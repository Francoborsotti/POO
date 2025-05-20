#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    adminDB = new Admindb(this);
    adminDB->conectar("../ejercicio_16");

    setUsuario();

    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validarUsuario()));
    connect(ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validarUsuario()));
    connect(ui->pbAgregar, SIGNAL(clicked()), this, SLOT(slot_agregarUsuario()));
}

Login::~Login()
{
    delete ui;
}

void Login::setUsuario()
{
    ui->leUsuario->setText(adminDB->setUsuariodb());
}


void Login::slot_validarUsuario()
{
    if (adminDB->validarUsuario("usuarios", ui->leUsuario->text(), ui->leClave->text())){
        this->close();
    }else {
        ui->leClave->clear();
    }
}

void Login::slot_agregarUsuario()
{
    if (adminDB->agregarUsuario("usuarios", ui->leUsuario->text(), ui->leClave->text())){
        this->close();
    }else {
        ui->leClave->clear();
        ui->leUsuario->clear();
    }
}

