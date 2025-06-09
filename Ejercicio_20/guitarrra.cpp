#include "guitarra.h"

Guitarra::Guitarra(int cuerdas, const QString &marca)
    : Instrumento(marca), m_cuerdas(cuerdas)
{
}

void Guitarra::sonar() const
{
    qDebug() << "Guitarra suena...";
}

int Guitarra::getCuerdas() const
{
    return m_cuerdas;
}

void Guitarra::setCuerdas(int cuerdas)
{
    m_cuerdas = cuerdas;
}
