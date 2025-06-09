#include <QCoreApplication>
#include <vector>
#include <iostream>

#include "instrumento.h"
#include "guitarra.h"
#include "bateria.h"
#include "teclado.h"
#include "electrico.h"

int main(int argc, char *argv[])
{


    qDebug() << "--- Creando Instrumentos ---";
    std::vector<Instrumento*> orquesta;

    orquesta.push_back(new Guitarra());
    orquesta.push_back(new Bateria(4, "Pearl"));
    orquesta.push_back(new Teclado(88, "Roland", 110));
    orquesta.push_back(new Guitarra(7, "Ibanez"));
    orquesta.push_back(new Teclado());

    qDebug() << "\n--- Mostrando Marcas y Sonando ---";
    for (Instrumento* instrumentoPtr : orquesta) {
        if (instrumentoPtr) {
            instrumentoPtr->verlo();
            instrumentoPtr->sonar();
            qDebug() << "--------------------";
        }
    }

    qDebug() << "\n--- Destruyendo Instrumentos ---";

    for (Instrumento* instrumentoPtr : orquesta) {
        delete instrumentoPtr;
    }
    orquesta.clear();

    qDebug() << "\n--- Fin del Programa ---";
    return 0;
}
