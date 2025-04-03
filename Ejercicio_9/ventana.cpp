#include "ventana.h"
#include <QPainter>

Ventana::Ventana()
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply *)));
    QNetworkRequest req(QUrl("https://www.anipedia.net/imagenes/que-comen-los-perros.jpg"));
    manager.get(req);
}

void Ventana::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawImage(0, 0, this->image.scaled(this->width(), this->height()));
}

void Ventana::slot_descargaFinalizada(QNetworkReply * reply)
{
    image = QImage::fromData( reply->readAll() );
    this->repaint();
}
