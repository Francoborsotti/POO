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

bool AdminDB::conectar(QString archivoSqlite)
{
    db.setDatabaseName(archivoSqlite);

    if(db.open()){
        return true;
    }else {
        qDebug() << "Error al conectar a la base de datos:" << db.lastError().text();
        return false;
    };
}

QSqlDatabase AdminDB::getDB(){
    return db;
}

bool AdminDB::validarUsuario(QString tabla, QString usuario, QString clave)
{
    this->setUsuarioActual(usuario);

    if(db.open()){
        QSqlQuery query = db.exec("SELECT nombre,apellido FROM " + tabla + " WHERE usuario = '" + usuario + "' AND clave = '" + clave + "'");

        while(query.next()){
            db.exec("UPDATE " + tabla + " SET ultimo_ingreso = CURRENT_TIMESTAMP WHERE usuario = '" + usuario + "';").next();
            //qDebug() << query.value(0).toString() << "" << query.value(1).toString();
            return true;
        }
    }
    return false;
}

void AdminDB::setUsuarioActual(const QString &usuario)
{
    usuarioActual = usuario;  // Almacena el usuario logueado
}

QString AdminDB::getUsuarioActual() const
{
    return usuarioActual;  // Devuelve el usuario logueado
}
