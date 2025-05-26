#include "cajamedicamento.h"

CajaMedicamento::CajaMedicamento(float dosis)
    : id(0), dosisTotales(dosis) // ID es 0 para indicar que no viene de la BD aún
{
    if (this->dosisTotales < 0) this->dosisTotales = 0; // Asegurar que no sea negativo
}

CajaMedicamento::CajaMedicamento(int id, float dosis)
    : id(id), dosisTotales(dosis)
{
    if (this->dosisTotales < 0) this->dosisTotales = 0; // Asegurar que no sea negativo
}

int CajaMedicamento::getId() const
{
    return id;
}

float CajaMedicamento::getDosisTotales() const
{
    return dosisTotales;
}

CajaMedicamento CajaMedicamento::operator+(const CajaMedicamento &otra) const
{
    // La nueva caja sumada no tiene ID de la base de datos (ID será 0).
    return CajaMedicamento(this->dosisTotales + otra.dosisTotales);
}

bool CajaMedicamento::operator==(const CajaMedicamento &otra) const
{
    // Compara si tienen la misma cantidad de dosis, con una pequeña tolerancia para floats.
    return qAbs(this->dosisTotales - otra.dosisTotales) < 0.001f;
}

QString CajaMedicamento::toString() const
{
    return QString("CajaMedicamento [ID: %1, Dosis: %2]")
    .arg(this->id == 0 ? "N/A" : QString::number(this->id)) // Si ID es 0, es nueva
        .arg(this->dosisTotales, 0, 'f', 1); // Formato con 1 decimal
}
