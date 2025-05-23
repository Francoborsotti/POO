#include "obstaculo.h"

Obstaculo::Obstaculo(QWidget *parent) : QWidget(parent)
{
}

Obstaculo::~Obstaculo()
{
}

QRect Obstaculo::getRect() const
{
    return this->geometry();
}

void Obstaculo::setPosicion(int x, int y)
{
    this->posicion.setX(x);
    this->posicion.setY(y);
    this->move(x, y);
}

QPoint Obstaculo::getPosicion() const
{
    return this->posicion;
}
