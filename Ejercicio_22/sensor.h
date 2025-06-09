#ifndef SENSOR_H
#define SENSOR_H

#include <QRandomGenerator> // Para generar números aleatorios

class Sensor
{
public:
    explicit Sensor();

    // getValorBruto() -> inline implícito (definido dentro de la clase)
    int getValorBruto() {
        return valorActual;
    }

    // getValorBrutoOffline() -> offline (definido fuera de la clase sin inline)
    int getValorBrutoOffline();

    // getValorNormalizado() -> inline explícito
    inline double getValorNormalizado() {
        return static_cast<double>(valorActual) / 1023.0;
    }

    // getValorNormalizadoOffline() -> offline (definido fuera de la clase sin inline)
    double getValorNormalizadoOffline();

private:
    int valorActual;
};

#endif // SENSOR_H
