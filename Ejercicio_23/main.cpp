#include <QCoreApplication> // Clase base para aplicaciones de consola Qt
#include <QDebug>           // Para mostrar mensajes en la consola
#include "cuentabancaria.h" // Incluimos nuestra clase CuentaBancaria

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Inicializa la aplicación de consola Qt

    qDebug() << "--- Demostración de Cuentas Bancarias y Función Amiga ---";

    // Creamos dos objetos CuentaBancaria
    CuentaBancaria cuenta1(1500); // Saldo inicial: 1500
    CuentaBancaria cuenta2(1000); // Saldo inicial: 1000

    qDebug() << "\nEstado inicial de las cuentas:";
    qDebug() << "Cuenta 1:";
    cuenta1.mostrar();
    qDebug() << "Cuenta 2:";
    cuenta2.mostrar();

    // Comparamos los saldos usando la función amiga
    qDebug() << "\nComparando saldos inicialmente:";
    bool resultado1 = compararSaldo(cuenta1, cuenta2);
    qDebug() << "Resultado de la comparación (Cuenta1 > Cuenta2):" << resultado1;

    // Realizamos algunas operaciones de depósito
    qDebug() << "\nRealizando depósitos:";
    cuenta1.depositar(300); // Cuenta 1: 1500 + 300 = 1800
    cuenta2.depositar(800); // Cuenta 2: 1000 + 800 = 1800

    qDebug() << "\nEstado de las cuentas después de depósitos:";
    qDebug() << "Cuenta 1:";
    cuenta1.mostrar();
    qDebug() << "Cuenta 2:";
    cuenta2.mostrar();

    // Volvemos a comparar los saldos después de los depósitos
    qDebug() << "\nComparando saldos después de depósitos:";
    bool resultado2 = compararSaldo(cuenta1, cuenta2);
    qDebug() << "Resultado de la comparación (Cuenta1 > Cuenta2):" << resultado2;

    // Otro depósito para cuenta2 para que tenga más saldo
    qDebug() << "\nOtro depósito para Cuenta 2:";
    cuenta2.depositar(100); // Cuenta 2: 1800 + 100 = 1900

    qDebug() << "\nEstado final de las cuentas:";
    qDebug() << "Cuenta 1:";
    cuenta1.mostrar();
    qDebug() << "Cuenta 2:";
    cuenta2.mostrar();

    // Última comparación
    qDebug() << "\nÚltima comparación de saldos:";
    bool resultado3 = compararSaldo(cuenta1, cuenta2);
    qDebug() << "Resultado de la comparación (Cuenta1 > Cuenta2):" << resultado3;

    return 0; // La aplicación de consola termina aquí
}
