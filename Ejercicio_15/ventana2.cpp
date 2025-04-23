#include "ventana2.h"
#include "ui_ventana2.h"

Ventana2::Ventana2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana2)
{
    ui->setupUi(this);
}

Ventana2::~Ventana2()
{
    delete ui;
}
