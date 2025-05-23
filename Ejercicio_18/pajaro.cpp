#include "pajaro.h"
#include <QPainter>
#include <QDebug>
#include <cstdlib>

Pajaro::Pajaro(QWidget *parent) : Obstaculo(parent),
    colorPajaro(Qt::red),
    velocidadHorizontal(5)
{
    radioPajaro = PAJARO_RADIO_MIN + (std::rand() % (PAJARO_RADIO_MAX - PAJARO_RADIO_MIN + 1));
    this->setFixedSize(radioPajaro * 2, radioPajaro * 2);
    timerMovimientoPropio = new QTimer(this);
    connect(timerMovimientoPropio, SIGNAL(timeout()), this, SLOT(slotMoverIzquierda()));
    this->show();
}

Pajaro::~Pajaro()
{
}

void Pajaro::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(colorPajaro);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(this->rect());
}

void Pajaro::iniciarMovimiento(int velocidad) {
    velocidadHorizontal = velocidad;
    if (velocidadHorizontal <= 0) velocidadHorizontal = 1;
    if (!timerMovimientoPropio->isActive()) {
        timerMovimientoPropio->start(30 + std::rand()%15);
    }
}

void Pajaro::detenerMovimiento() {
    timerMovimientoPropio->stop();
}

void Pajaro::slotMoverIzquierda()
{
    this->move(this->x() - velocidadHorizontal, this->y());
}
