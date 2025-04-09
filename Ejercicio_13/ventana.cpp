#include "ventana.h"
#include "ui_ventana.h"

#include <QPainter>
#include <QImage>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
{
    ui->setupUi(this);

    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    QNetworkRequest req(QUrl("https://th.bing.com/th/id/OIP.igCbnp374usKXWniHYMmdgHaEK?w=1920&h=1080&rs=1&pid=ImgDetMain"));
    manager.get(req);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, this->image.scaled(this->width(), this->height()));
}

void Ventana::slot_descargaFinalizada(QNetworkReply *reply)
{
    image = QImage::fromData(reply->readAll());
    this->repaint();
}
