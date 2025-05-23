#include "trex.h"
#include <QDebug>

TRex::TRex(QWidget *parent) : QWidget(parent),
    estadoActual(Corriendo),
    colorTRex(Qt::darkGray),
    velocidadY(0),
    alturaSuelo(200),
    velocidadX(0),
    anchoActual(TREX_ANCHO_BASE),
    altoActual(TREX_ALTO_BASE)
{
    actualizarDimensiones();
    posXInicial = 50;
    this->show();
}

TRex::~TRex()
{
}

void TRex::actualizarDimensiones() {
    if (estadoActual == Agachado) {
        altoActual = TREX_ALTO_AGACHADO;
    } else {
        altoActual = TREX_ALTO_BASE;
    }
    anchoActual = TREX_ANCHO_BASE;
    this->setFixedSize(anchoActual, altoActual);
}

void TRex::setAlturaSuelo(int altura) {
    alturaSuelo = altura;
    if (estadoActual != Saltando) {
        this->move(this->x(), alturaSuelo - altoActual);
    }
    posYInicial = alturaSuelo - TREX_ALTO_BASE;
}

void TRex::resetear() {
    estadoActual = Corriendo;
    velocidadY = 0;
    velocidadX = 0;
    actualizarDimensiones();
    this->move(posXInicial, alturaSuelo - altoActual);
    this->update();
}

void TRex::saltar()
{
    if (estadoActual != Saltando) {
        estadoActual = Saltando;
        velocidadY = FUERZA_SALTO_INICIAL_TREX;
        actualizarDimensiones();
        this->update();
    }
}

void TRex::agacharse()
{
    if (estadoActual == Corriendo) {
        estadoActual = Agachado;
        actualizarDimensiones();
        this->move(this->x(), alturaSuelo - altoActual);
        this->update();
    }
}

void TRex::dejarDeAgacharse()
{
    if (estadoActual == Agachado) {
        estadoActual = Corriendo;
        actualizarDimensiones();
        this->move(this->x(), alturaSuelo - altoActual);
        this->update();
    }
}

void TRex::actualizarPosicion()
{
    if (velocidadX != 0) {
        int nuevaPosX = this->x() + velocidadX;
        if (this->parentWidget()) {
            if (nuevaPosX < 0) nuevaPosX = 0;
            if (nuevaPosX + this->width() > this->parentWidget()->width()) {
                nuevaPosX = this->parentWidget()->width() - this->width();
            }
        }
        this->move(nuevaPosX, this->y());
        velocidadX = 0;
    }

    if (estadoActual == Saltando) {
        int nuevaPosY = this->y() + velocidadY;
        velocidadY += GRAVEDAD_TREX;

        if (nuevaPosY >= (alturaSuelo - altoActual)) {
            nuevaPosY = alturaSuelo - altoActual;
            estadoActual = Corriendo;
            velocidadY = 0;
            actualizarDimensiones();
        }
        this->move(this->x(), nuevaPosY);
    }
}

QRect TRex::getRect() const
{
    return this->geometry();
}

void TRex::setVelocidadX(int vel) {
    this->velocidadX = vel;
}

void TRex::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), colorTRex);
}
