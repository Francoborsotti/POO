#include "cuentabancaria.h"

// Implementación del constructor
CuentaBancaria::CuentaBancaria(int saldoInicial) : saldo(saldoInicial)
{
    // No necesitamos hacer nada más aquí, el inicializador de miembros ya asigna el saldo.
}

// Implementación del método depositar
void CuentaBancaria::depositar(int monto)
{
    if (monto > 0) {
        saldo += monto;
        qDebug() << "Depósito de" << monto << "realizado. Nuevo saldo:" << saldo;
    } else {
        qDebug() << "Error: El monto a depositar debe ser positivo.";
    }
}

// Implementación del método mostrar
void CuentaBancaria::mostrar() const
{
    qDebug() << "Saldo actual:" << saldo;
}

bool compararSaldo(CuentaBancaria cuenta1, CuentaBancaria cuenta2)
{
    // Acceso directo a 'saldo' (miembro privado) de ambos objetos CuentaBancaria
    if (cuenta1.saldo > cuenta2.saldo) {
        qDebug() << "Cuenta 1 tiene mayor saldo que Cuenta 2.";
        return true;
    } else {
        qDebug() << "Cuenta 1 NO tiene mayor saldo que Cuenta 2.";
        return false;
    }
}
