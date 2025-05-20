#include "admindb.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QCryptographicHash>

Admindb::Admindb(QWidget *parent)
    : QWidget{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool Admindb::conectar(QString archivoSqlite)
{
    db.setDatabaseName(archivoSqlite);

    if(db.open()){
        return true;
    }else {
        qDebug() << "Error al conectar a la base de datos" << db.lastError().text();
        return false;
    };
}

QSqlDatabase Admindb::getDB()
{
    return db;
}

bool Admindb::validarUsuario(QString tabla, QString usuario, QString clave)
{
    QByteArray claveMd5 = QCryptographicHash::hash(clave.toUtf8(), QCryptographicHash::Md5).toHex();

    // Preparar la consulta SQL
    QString consulta = QString("SELECT COUNT(*) FROM %1 WHERE usuario = ? AND clave_md5 = ?").arg(tabla);
    QSqlQuery query;
    query.prepare(consulta);
    query.addBindValue(usuario);
    query.addBindValue(claveMd5);

    if (query.exec()) {
        if (query.next() && query.value(0).toInt() > 0) {
            QSqlQuery query;
            query.exec("DELETE FROM ultimo_login"); // Limpiar el registro anterior
            query.prepare("INSERT INTO ultimo_login (usuario) VALUES (?)");
            query.addBindValue(usuario);
            query.exec();
            return true; // Usuario y clave correctos
        }
    } else {
        qWarning() << "Error en la consulta:" << query.lastError().text();
    }
    return false;
}

QString Admindb::setUsuariodb()
{
    QSqlQuery query(db);
    if (query.exec("SELECT usuario FROM ultimo_login WHERE id = 1")) {
        if (query.next()) {
            QString usuario = query.value(0).toString();
            return usuario;
        } else {
            return "";
        }
    } else {
        qWarning() << "Error en la consulta:" << query.lastError().text();
        return "";
    }
    db.close();
}

bool Admindb::agregarUsuario(QString tabla, QString usuario, QString clave)
{
    // La base de datos debe estar abierta antes de llamar a esta función

    // Calcular el hash MD5 de la clave
    QByteArray claveMd5 = QCryptographicHash::hash(clave.toUtf8(), QCryptographicHash::Md5).toHex();

    // Preparar la consulta SQL para insertar el usuario
    QString consulta = QString("INSERT INTO %1 (usuario, clave_md5) VALUES (?, ?)").arg(tabla);
    QSqlQuery query;
    query.prepare(consulta);
    query.addBindValue(usuario);
    query.addBindValue(claveMd5);

    if (query.exec()) {
        return true; // Usuario agregado correctamente
    } else {
        qWarning() << "Error al insertar el usuario:" << query.lastError().text();
        return false;
    }
}
