#include "ventana.h"
#include "ui_ventana.h"

Ventana::Logi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
