#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    adminBD(AdminDB::getInstancia()) {

    ui->setupUi(this);

    // Conectar a la base de datos
    adminBD->conectar();

    // Conectar señales y slots
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(agregarCaja())); // Botón Agregar
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(sumarCajas())); // Botón Sumar
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(compararCajas())); // Botón Comparar

    // Cargar cajas existentes en la lista
    QList<CajaMedicamento> cajas = adminBD->obtenerTodas();
    foreach (const CajaMedicamento &caja, cajas) {
        ui->listWidget->addItem(caja.toString());
    }
}

Widget::~Widget() {
    delete ui;
}

void Widget::agregarCaja() {
    // Obtener la cantidad de dosis de la entrada
    float dosis = ui->spinBox->value();

    // Intentar agregar la caja a la base de datos
    if (adminBD->insertarCaja(dosis)) {
        // Si se agrega con éxito, actualizar la lista
        ui->listWidget->addItem(QString("Caja nueva [Dosis: %1]").arg(dosis));
    } else {
        // Mostrar advertencia si se supera el límite
        QMessageBox::warning(this, "Error", "No se puede agregar. Se supera el límite de dosis.");
    }
}

void Widget::sumarCajas() {
    // Obtener las cajas seleccionadas
    QList<QListWidgetItem *> seleccionados = ui->listWidget->selectedItems();

    if (seleccionados.size() != 2) {
        QMessageBox::warning(this, "Error", "Seleccione exactamente dos cajas.");
        return;
    }

    // Obtener índices de las cajas seleccionadas
    int index1 = ui->listWidget->row(seleccionados[0]);
    int index2 = ui->listWidget->row(seleccionados[1]);

    // Obtener las cajas desde la base de datos
    QList<CajaMedicamento> cajas = adminBD->obtenerTodas();
    CajaMedicamento suma = cajas[index1] + cajas[index2];

    // Verificar si la suma excede el límite
    if (suma.getDosisTotales() > 1000) {
        QMessageBox::warning(this, "Error", "La suma excede el límite permitido.");
    } else {
        ui->listWidget->addItem(suma.toString());
    }
}

void Widget::compararCajas() {
    // Obtener las cajas seleccionadas
    QList<QListWidgetItem *> seleccionados = ui->listWidget->selectedItems();

    if (seleccionados.size() != 2) {
        QMessageBox::warning(this, "Error", "Seleccione exactamente dos cajas.");
        return;
    }

    // Obtener índices de las cajas seleccionadas
    int index1 = ui->listWidget->row(seleccionados[0]);
    int index2 = ui->listWidget->row(seleccionados[1]);

    // Obtener las cajas desde la base de datos
    QList<CajaMedicamento> cajas = adminBD->obtenerTodas();
    bool iguales = cajas[index1] == cajas[index2];

    // Mostrar el resultado en la consola
    qDebug() << "Las cajas seleccionadas son" << (iguales ? "iguales" : "diferentes");
}
