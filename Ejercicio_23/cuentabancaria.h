#ifndef CUENTABANCARIA_H
#define CUENTABANCARIA_H

#include <QDebug> // Para usar qDebug() en el método mostrar()

// Declaración forward de la clase CuentaBancaria.
// Necesaria para que la función amiga pueda declararse antes de que CuentaBancaria esté completamente definida.
class CuentaBancaria;

class CuentaBancaria
{
public:
    // Constructor que recibe el saldo inicial
    explicit CuentaBancaria(int saldoInicial);

    // Método para depositar dinero en la cuenta
    void depositar(int monto);

    // Método para mostrar el saldo actual
    void mostrar() const; // const porque no modifica el estado del objeto

    // Declaración de la función amiga.
    // Esto otorga a la función 'compararSaldo' acceso a los miembros privados de CuentaBancaria.
    friend bool compararSaldo(CuentaBancaria cuenta1, CuentaBancaria cuenta2);

private:
    int saldo; // Atributo privado: el saldo de la cuenta
};

#endif // CUENTABANCARIA_H
