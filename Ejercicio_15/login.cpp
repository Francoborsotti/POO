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

    adminDB = new AdminDB(this);
    adminDB->conectar("../test");
}

Login::~Login()
{
    delete ui;
}

void Login::slot_validarUsuario()
{


    if (adminDB->validarUsuario("usuarios", ui->leUsuario->text(), ui->leClave->text())){
        qDebug() << "funciona";
    }else{
        qDebug()<< "no fun";
    }
    //if(ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234"){
    //    ventana->show();
    //    this->close();
    //}
}
