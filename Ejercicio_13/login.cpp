#include "login.h"
#include "ui_login.h"
#include "ventana.h"
#include <QNetworkAccesManager>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    QImage im("../../fondo_login.png");

    connect(ui->pbIngresar, SIGNAL(pressed()),this , SLOT(slot_validarUsuario()));
    connect(ui->leClave, SIGNAL(returnPressed()),this , SLOT(slot_validarUsuario()));

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_setFondo(QNetworkReply*)));

    QUrl imageUrl("https://www.anipedia.net/imagenes/que-comen-los-perros.jpg");
    QNetworkRequest request(imageUrl);
    manager->get(request);
}

Login::~Login()
{
    delete ui;
}

void Login::slot_validarUsuario()
{
    if(ui->leUsuario->text() == "admin" && ui->leClave->text() == "1234"){
        //Ventana *ventana = new Ventana;
        //ventana->show();
        this->close();
    }else{
        ui->leClave->clear();
    }
}

void Login::slot_setFondo()
{

}
