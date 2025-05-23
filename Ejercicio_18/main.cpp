// main.cpp
#include "juegotrex.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JuegoTRex juego;
    juego.setWindowTitle("T-Rex Extremo (Pop-up)");
    juego.show();
    return a.exec();
}
