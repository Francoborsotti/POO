#include <QApplication> // Usamos QApplication para aplicaciones GUI
#include "benchmarkgui.h" // Incluimos nuestra nueva clase GUI

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Crea una instancia de la aplicación GUI

    BenchmarkGUI gui; // Crea una instancia de nuestra ventana GUI
    gui.show();        // Muestra la ventana

    return a.exec();   // Inicia el bucle de eventos de la aplicación Qt
}
