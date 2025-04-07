#include "ventana.h"
#include "./ui_ventana.h"

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
{
    ui->setupUi(this);

    connect(ui->pbSalir, SIGNAL(pressed()), this, SLOT(slot_salir()));

}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::slot_salir()
{
    this->close();
}
