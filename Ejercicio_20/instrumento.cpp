#include "instrumento.h"

Instrumento::Instrumento(const QString &marca) : m_marca(marca)
{
}

Instrumento::~Instrumento()
{
}

void Instrumento::verlo() const
{
    qDebug() << "Marca del instrumento:" << m_marca;
}

QString Instrumento::getMarca() const
{
    return m_marca;
}

void Instrumento::setMarca(const QString &marca)
{
    m_marca = marca;
}
