#include "admindb.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QCoreApplication> // Para applicationDirPath
#include <QDir>             // Para manejo de rutas (opcional, pero útil)

AdminDB* AdminDB::instancia = nullptr;

AdminDB* AdminDB::getInstance()
{
    if (instancia == nullptr) {
        instancia = new AdminDB();
    }
    return instancia;
}

AdminDB::AdminDB()
{
    // El constructor está vacío. La conexión se hace explícitamente.
}

AdminDB::~AdminDB()
{
    if (db.isOpen()) {
        db.close();
    }
}

QSqlError AdminDB::getLastError() {
    return db.lastError();
}

bool AdminDB::conectar(const QString& nombreArchivo)
{
    const QString nombreConexion = "GestionMedicamentosDBConexion";
    if (QSqlDatabase::contains(nombreConexion)) {
        db = QSqlDatabase::database(nombreConexion);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", nombreConexion);
    }

    // Crear la base de datos en la carpeta del ejecutable
    QString rutaBaseDatos = QCoreApplication::applicationDirPath() + QDir::separator() + nombreArchivo;
    db.setDatabaseName(rutaBaseDatos);

    if (!db.open()) {
        qWarning() << "AdminDB Error: No se pudo abrir/crear la base de datos en" << rutaBaseDatos << ":" << db.lastError().text();
        return false;
    }

    qDebug() << "AdminDB: Base de datos conectada/creada exitosamente en:" << rutaBaseDatos;
    if (!crearTablaSiNoExiste()) {
        // Si la tabla no se puede crear, la conexión no es realmente útil
        db.close();
        QSqlDatabase::removeDatabase(nombreConexion);
        return false;
    }
    return true;
}

void AdminDB::desconectar()
{
    if (db.isOpen()) {
        QString dbNameOriginal = db.databaseName();
        QString connName = db.connectionName();
        db.close();
        qDebug() << "AdminDB: Base de datos desconectada (" << dbNameOriginal << ").";
        QSqlDatabase::removeDatabase(connName);
    }
}

bool AdminDB::crearTablaSiNoExiste()
{
    QSqlQuery query(db);
    QString sql = "CREATE TABLE IF NOT EXISTS cajas_medicamentos ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "dosis_totales REAL NOT NULL CHECK(dosis_totales > 0.0)" // Las dosis deben ser positivas
                  ");";
    if (!query.exec(sql)) {
        qWarning() << "AdminDB Error: Al crear la tabla cajas_medicamentos:" << query.lastError().text();
        return false;
    }
    qDebug() << "AdminDB: Tabla 'cajas_medicamentos' verificada/creada exitosamente.";
    return true;
}

float AdminDB::obtenerTotalDosisActuales()
{
    QSqlQuery query(db);
    query.prepare("SELECT SUM(dosis_totales) FROM cajas_medicamentos");
    if (query.exec() && query.next()) {
        QVariant val = query.value(0);
        if (val.isNull() || !val.isValid()) {
            return 0.0f;
        }
        return val.toFloat();
    } else {
        qWarning() << "AdminDB Error: Al obtener el total de dosis:" << query.lastError().text();
        return 0.0f; // Devolver 0.0f en caso de error o si no hay datos
    }
}

bool AdminDB::insertarCaja(float dosis)
{
    if (dosis <= 0.0f) {
        qWarning() << "AdminDB Error: Intento de insertar caja con dosis no positivas:" << dosis;
        return false;
    }

    float totalActual = obtenerTotalDosisActuales();

    // Usar una pequeña épsilon para comparaciones de punto flotante
    if ((totalActual + dosis) > (LIMITE_MAXIMO_DOSIS_TOTALES + 0.001f)) {
        qWarning() << "AdminDB Info: No se puede insertar la caja. Dosis actuales:" << totalActual
                   << ", Dosis a agregar:" << dosis
                   << ". Límite (" << LIMITE_MAXIMO_DOSIS_TOTALES << ") excedido.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO cajas_medicamentos (dosis_totales) VALUES (:dosis)");
    query.bindValue(":dosis", dosis);

    if (!query.exec()) {
        qWarning() << "AdminDB Error: Al insertar caja:" << query.lastError().text();
        return false;
    }
    qDebug() << "AdminDB: Caja insertada exitosamente con dosis:" << dosis << ". Nuevo total:" << obtenerTotalDosisActuales();
    return true;
}

QList<CajaMedicamento> AdminDB::obtenerTodas()
{
    QList<CajaMedicamento> listaCajas;
    QSqlQuery query(db);
    // Ordenar por ID para consistencia, por ejemplo, del más antiguo al más nuevo
    query.prepare("SELECT id, dosis_totales FROM cajas_medicamentos ORDER BY id ASC");

    if (query.exec()) {
        while (query.next()) {
            int id = query.value("id").toInt();
            float dosis = query.value("dosis_totales").toFloat();
            listaCajas.append(CajaMedicamento(id, dosis));
        }
    } else {
        qWarning() << "AdminDB Error: Al obtener todas las cajas:" << query.lastError().text();
    }
    return listaCajas;
}

bool AdminDB::reemplazarDosCajasConSuma(int idCaja1, int idCaja2, float dosisSuma)
{
    if (dosisSuma <= 0.0f) {
        qWarning() << "AdminDB Error: La dosis suma para reemplazar no puede ser cero o negativa.";
        return false;
    }
    // El límite de 1000 para la caja individual ya se chequea en la GUI.
    // El límite total de la obra social no se altera con esta operación.

    if (!db.transaction()) {
        qWarning() << "AdminDB Error: No se pudo iniciar la transacción para reemplazar cajas:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    bool exitoParcial = true;

    // Eliminar primera caja
    query.prepare("DELETE FROM cajas_medicamentos WHERE id = :id");
    query.bindValue(":id", idCaja1);
    if (!query.exec()) {
        qWarning() << "AdminDB Error: Al eliminar caja (ID:" << idCaja1 << ") en reemplazo:" << query.lastError().text();
        exitoParcial = false;
    }

    // Eliminar segunda caja (solo si la primera eliminación fue exitosa)
    if (exitoParcial) {
        query.prepare("DELETE FROM cajas_medicamentos WHERE id = :id");
        query.bindValue(":id", idCaja2);
        if (!query.exec()) {
            qWarning() << "AdminDB Error: Al eliminar caja (ID:" << idCaja2 << ") en reemplazo:" << query.lastError().text();
            exitoParcial = false;
        }
    }

    // Insertar la nueva caja con la suma (solo si las eliminaciones fueron exitosas)
    if (exitoParcial) {
        query.prepare("INSERT INTO cajas_medicamentos (dosis_totales) VALUES (:dosis)");
        query.bindValue(":dosis", dosisSuma);
        if (!query.exec()) {
            qWarning() << "AdminDB Error: Al insertar caja sumada en reemplazo:" << query.lastError().text();
            exitoParcial = false;
        }
    }

    if (exitoParcial) {
        if (db.commit()) {
            qDebug() << "AdminDB: Cajas" << idCaja1 << "y" << idCaja2 << "reemplazadas con nueva caja de" << dosisSuma << "dosis.";
            return true;
        } else {
            qWarning() << "AdminDB Error: Al hacer commit de la transacción de reemplazo:" << db.lastError().text();
            db.rollback(); // Intentar rollback si el commit falla
            return false;
        }
    } else {
        qWarning() << "AdminDB Info: Error durante la operación de reemplazo. Haciendo rollback.";
        db.rollback();
        return false;
    }
}
