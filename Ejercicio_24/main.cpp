#include <QCoreApplication> // Clase base para aplicaciones de consola Qt
#include <QDebug>           // Para mostrar mensajes en la consola
#include "persona.h"        // Incluimos nuestra clase Persona

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Inicializa la aplicación de consola Qt

    qDebug() << "--- Demostración de Miembros Static en C++ ---";

    // Mostramos el total de personas antes de crear cualquier instancia.
    // Se llama directamente usando el nombre de la clase.
    qDebug() << "Total de personas al inicio:" << Persona::totalPersonas();

    // Creamos varias instancias de Persona
    Persona p1("Alice");
    Persona p2("Bob");
    Persona p3("Charlie");

    // Mostramos el total de personas después de crear algunas instancias.
    // De nuevo, usando el método estático de la clase.
    qDebug() << "\nTotal de personas después de crear 3 instancias:" << Persona::totalPersonas();

    // Creamos una persona en un bloque de ámbito para ver cómo el destructor afecta el contador
    {
        Persona p4("David");
        qDebug() << "Total de personas dentro del bloque:" << Persona::totalPersonas();
    } // p4 es destruida aquí cuando el bloque finaliza

    qDebug() << "\nTotal de personas después de que 'David' fue destruido (salió del ámbito):" << Persona::totalPersonas();

    // También podemos mostrar los nombres de las personas individuales
    qDebug() << "\nMostrando nombres de personas individuales:";
    p1.mostrar();
    p2.mostrar();
    p3.mostrar();

    // Puedes destruir una persona explícitamente (aunque no es común con objetos en el stack)
    // Pero si p2 fuera un puntero a un objeto en el heap, lo haríamos:
    // Persona* p_heap = new Persona("Eve");
    // qDebug() << "Total de personas con Eve:" << Persona::totalPersonas();
    // delete p_heap; // Esto llamaría al destructor y decrementar el contador
    // qDebug() << "Total de personas sin Eve:" << Persona::totalPersonas();


    qDebug() << "\nLa aplicación finalizará. Las personas restantes (Alice, Bob, Charlie) serán destruidas.";
    // Cuando main() finaliza, los objetos p1, p2, p3 serán destruidos automáticamente,
    // y el destructor de Persona decremetará el contador.

    return 0; // La aplicación de consola termina aquí
}
