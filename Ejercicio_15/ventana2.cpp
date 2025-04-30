#include "ventana2.h"
#include "ui_ventana2.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Ventana2::Ventana2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana2)
{
    ui->setupUi(this);

    adminDB = new AdminDB(this);
    adminDB->conectar("../test");

    mostrarUltimosUsuarios();
}

Ventana2::~Ventana2()
{
    delete ui;
}

void Ventana2::mostrarUltimosUsuarios()
{
    QSqlDatabase db = adminDB->getDB();

    if (!db.isOpen()) {
        qDebug() << "Error: La conexión a la base de datos no está abierta.";
        return;
    }

    QSqlQuery query(db);

    if (query.exec("SELECT nombre, apellido FROM usuarios ORDER BY ultimo_ingreso DESC LIMIT 2")) {
        qDebug() << "Consulta ejecutada correctamente.";

        int contador = 0;

        while (query.next()) {
            QString nombre = query.value(0).toString();
            QString apellido = query.value(1).toString();

            if (contador == 0) {
                ui->lUsuarioActual->setText("Usuario 1: " + nombre + " " + apellido);
            } else if (contador == 1) {
                ui->lUsuarioAnterior->setText("Usuario 2: " + nombre + " " + apellido);
            }

            contador++;
        }

        if (contador < 1) {
            ui->lUsuarioActual->setText("Usuario 1: No disponible");
        }
        if (contador < 2) {
            ui->lUsuarioAnterior->setText("Usuario 2: No disponible");
        }

    } else {
        qDebug() << "Error en la consulta:" << query.lastError().text();
    }
}
