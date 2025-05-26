#ifndef CAJAMEDICAMENTO_H
#define CAJAMEDICAMENTO_H

#include <QString>
#include <QtGlobal> // Para qAbs, necesario para la comparación de floats

class CajaMedicamento
{
public:
    // Constructor para crear una nueva caja (sin ID, se asignará por la BD)
    explicit CajaMedicamento(float dosis);

    // Constructor para cargar una caja desde la base de datos
    CajaMedicamento(int id, float dosis);

    int getId() const;
    float getDosisTotales() const;

    // Operadores
    CajaMedicamento operator+(const CajaMedicamento &otra) const;
    bool operator==(const CajaMedicamento &otra) const; // Compara dosis

    QString toString() const;

private:
    int id; // 0 si es una caja nueva no persistida
    float dosisTotales;
};

#endif // CAJAMEDICAMENTO_H
