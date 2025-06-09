#include "teclado.h"

Teclado::Teclado(int teclas, const QString &marca, int voltaje)
    : Instrumento(marca),
    Electrico(voltaje),
    m_teclas(teclas)
{
}

Teclado::~Teclado()
{
    qDebug() << "Teclado guardado en su funda.";
}

void Teclado::sonar() const
{
    qDebug() << "Teclado suena...";
}

void Teclado::verlo() const
{
    Instrumento::verlo();
    qDebug() << "  Tipo: Teclado, Teclas:" << m_teclas << ", Voltaje:" << Electrico::getVoltaje() << "V";
}

int Teclado::getTeclas() const
{
    return m_teclas;
}

void Teclado::setTeclas(int teclas)
{
    m_teclas = teclas;
}
