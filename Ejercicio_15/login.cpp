#include "login.h"
#include "ui_login.h"

#include <QDebug>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    ventana = new Ventana2;

    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validarUsuario()));
    connect(ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validarUsuario()));

    adminDB = new AdminDB;
    qDebug() << "La base se abrio correctamente" << adminDB->conectar("../test");
}

Login::~Login()
{
    delete ui;
}

void Login::slot_validarUsuario()
{
    adminDB->validarUsuario("usuarios", ui->leUsuario->text(), ui->leClave->text());
}
