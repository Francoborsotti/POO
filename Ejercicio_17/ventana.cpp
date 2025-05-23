#include "ventana.h"
#include "ui_ventana.h"
#include "boton.h"

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);

    // Ejemplo: si tuviste objetos llamados boton1, boton2, ..., en Qt Designer
    qobject_cast<Boton*>(ui->boton1)->colorear(Boton::Magenta);
    qobject_cast<Boton*>(ui->boton2)->colorear(Boton::Azul);
    qobject_cast<Boton*>(ui->boton3)->colorear(Boton::Verde);
    qobject_cast<Boton*>(ui->boton4)->colorear(Boton::Magenta);
    qobject_cast<Boton*>(ui->boton5)->colorear(Boton::Azul);

    connect(qobject_cast<Boton*>(ui->boton1), &Boton::signal_clic, this, [](){
        qDebug("Botón 1 presionado");
    });
    // Repetir conexiones para los otros botones si es necesario
}

Ventana::~Ventana()
{
    delete ui;
}
