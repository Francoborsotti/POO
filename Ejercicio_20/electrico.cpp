#include "electrico.h"

Electrico::Electrico(int voltaje) : m_voltaje(voltaje)
{
    qDebug() << "Componente electrico conectado (Voltaje:" << m_voltaje << "V)";
}

Electrico::~Electrico()
{
    qDebug() << "Desenchufado (Voltaje:" << m_voltaje << "V)";
}

int Electrico::getVoltaje() const
{
    return m_voltaje;
}

void Electrico::setVoltaje(int voltaje)
{
    m_voltaje = voltaje;
}
