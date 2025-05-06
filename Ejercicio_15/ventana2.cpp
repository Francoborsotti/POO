#include "ventana2.h"
#include "ui_ventana2.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDialog>

Ventana2::Ventana2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana2)
{
    ui->setupUi(this);

    adminDB = new AdminDB(this);
    adminDB->conectar("../test");


}

Ventana2::~Ventana2()
{
    delete ui;
}

void Ventana2::setUsuarioActual(const QString &usuario)
{
    usuarioActual = usuario;
    qDebug() << "Usuario actual seteado a:" << usuario;
}

void Ventana2::mostrarUltimosUsuarios()
{
    QSqlDatabase db = adminDB->getDB();

    if (!db.isOpen()) {
        qDebug() << "Error: La conexión a la base de datos no está abierta.";
        return;
    }

    QSqlQuery query(db);

    // Consulta para obtener el nombre y la última fecha de conexión del usuario actual
    query.prepare("SELECT nombre, apellido, ultimo_ingreso FROM usuarios WHERE usuario = '" + usuarioActual + "'");

     qDebug() << "Consulta preparada:" << query.lastQuery();
    if (query.exec()) {
        qDebug() << "Consulta ejecutada correctamente.";

        if (query.next()) {
            QString nombre = query.value(0).toString();
            QString apellido = query.value(1).toString();
            QString ultimoIngreso = query.value(2).toString();

            // Mostrar el nombre completo del usuario
            ui->lUsuarioActual->setText("Usuario: " + nombre + " " + apellido);

            // Mostrar la última fecha de conexión
            ui->lUsuarioAnterior->setText("Última conexión: " + ultimoIngreso);
        } else {
            ui->lUsuarioActual->setText("Usuario: No disponible");
            ui->lUsuarioAnterior->setText("Última conexión: No disponible");
        }
    } else {
        qDebug() << "Error en la consulta:" << query.lastError().text();
    }
}
