#include "login.h"
#include "ui_login.h"
#include "ventana.h"

#include <QPainter>
#include <QImage>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    QNetworkRequest req(QUrl("https://th.bing.com/th/id/OIP.vuUXp1-R_fv3Ho-dGZYodAHaFu?w=1325&h=1024&rs=1&pid=ImgDetMain"));
    manager.get(req);

    connect(ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validarUsuario()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validarUsuario()));
}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, this->image.scaled(this->width(), this->height()));
}

void Login::slot_descargaFinalizada(QNetworkReply *reply)
{
    image = QImage::fromData(reply->readAll());
    this->repaint();
}

void Login::slot_validarUsuario()
{
    if (ui->leUSuario->text() == "admin" && ui->leClave->text() == "1234"){
        Ventana *ventana = new Ventana;
        ventana->show();
        this->close();

    }else{
        ui->leClave->clear();
    }
}
