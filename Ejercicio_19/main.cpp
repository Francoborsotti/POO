#include "widget.h"
#include "admindbmedicamentos.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AdminDB::getInstancia()->conectar();

    Widget w;
    w.show();
    return a.exec();
}
