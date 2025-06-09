#include <QApplication> // Incluye la clase base de la aplicación Qt
#include "htmlparsergui.h" // Incluye la definición de nuestra clase GUI

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Crea una instancia de la aplicación Qt

    HtmlParserGUI gui; // Crea una instancia de nuestra ventana principal GUI
    gui.show();        // Muestra la ventana

    return a.exec();   // Inicia el bucle de eventos de la aplicación Qt
}
