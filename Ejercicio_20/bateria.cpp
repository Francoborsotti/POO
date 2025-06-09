#include "bateria.h"

Bateria::Bateria(int tambores, const QString &marca)
    : Instrumento(marca), m_tambores(tambores)
{
}

void Bateria::sonar() const
{
    qDebug() << "Batería suena...";
}

int Bateria::getTambores() const
{
    return m_tambores;
}

void Bateria::setTambores(int tambores)
{
    m_tambores = tambores;
}
