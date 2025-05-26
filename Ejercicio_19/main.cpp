#include <QApplication>
#include <QLocale>
#include "gestionmedicamentoswidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale::C);

    GestionMedicamentosWidget ventanaPrincipal;
    ventanaPrincipal.show();

    return a.exec();
}
