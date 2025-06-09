#include "sensor.h"
// No QDebug aquí para mantener la clase Sensor agnóstica a la salida

// Constructor de la clase Sensor
Sensor::Sensor()
{
    valorActual = QRandomGenerator::global()->bounded(1024); // Rango [0, 1023]
}

// Implementación de getValorBrutoOffline()
int Sensor::getValorBrutoOffline()
{
    return valorActual;
}

// Implementación de getValorNormalizadoOffline()
double Sensor::getValorNormalizadoOffline()
{
    return static_cast<double>(valorActual) / 1023.0;
}
