#include "admindbmedicamentos.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

AdminDB * AdminDB::instancia = nullptr;

AdminDB::AdminDB()  {
}

AdminDB * AdminDB::getInstancia()  {
    if( instancia == nullptr )  {
        instancia = new AdminDB;
    }
    return instancia;
}

void AdminDB::conectar() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../ejercicio19");

    if (!db.open()) {
        qDebug() << "Error al conectar a la base de datos:" << db.lastError().text();
        return;
    }

    qDebug() << "Conexión a la base de datos establecida.";
}


