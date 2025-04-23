#include "admindb.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

AdminDB::AdminDB(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool AdminDB::conectar(QString archivoSqlite){
    db.setDatabaseName(archivoSqlite);

    if(db.open())
        return true;

    return false;
}

QSqlDatabase AdminDB::getDB(){
    return db;
}

bool AdminDB::validarUsuario(QString tabla, QString usuario, QString clave)
{
    if (tabla.isEmpty()) {
        qDebug() << "Error: El nombre de la tabla está vacío.";
        return false;
    }

    if (db.open()) {
        QSqlQuery query;

        // Preparar la consulta con parámetros nombrados
        QString consulta = "SELECT nombre, apellido FROM " + tabla +
                           " WHERE Carlos AND Gomez";
        query.prepare(consulta);

        if (query.exec()) {
            while (query.next()) {
                qDebug() << "Nombre:" << query.value(0).toString()
                << "Apellido:" << query.value(1).toString();
            }
        } else {
            // Mostrar el error si la consulta falla
            qDebug() << "Error en la consulta:" << query.lastError().text();
            return false;
        }
    } else {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return false;
    }

    return true;
}

