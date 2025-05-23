#include "cactus.h"
#include <cstdlib>
#include <QPainter>

Cactus::Cactus(QWidget *parent) : Obstaculo(parent), colorCactus(Qt::darkGreen)
{
    anchoCactus = CACTUS_ANCHO_MIN + (std::rand() % (CACTUS_ANCHO_MAX - CACTUS_ANCHO_MIN + 1));
    altoCactus = CACTUS_ALTO_MIN + (std::rand() % (CACTUS_ALTO_MAX - CACTUS_ALTO_MIN + 1));
    this->setFixedSize(anchoCactus, altoCactus);
    this->show();
}

void Cactus::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), colorCactus);
}
