#include <QApplication>
#include "ventana.h"

int main(int argc, char ** argv){
    QApplication a (argc, argv);

    Ventana mainWindow;
    mainWindow.show();

    return a.exec();
}
