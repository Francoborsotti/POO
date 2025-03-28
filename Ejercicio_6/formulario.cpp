#include "formulario.h"

Formulario::Formulario(QWidget *parent) : QWidget(parent) {
    lLegajo = new QLabel("Legajo:");
    lNombre = new QLabel("Nombre:");
    lApellido = new QLabel("Apellido:");
    leLegajo = new QLineEdit;
    leNombre = new QLineEdit;
    leApellido = new QLineEdit;
    pbEnviar = new QPushButton("Enviar");

    layout.addWidget(lLegajo, 0, 0);
    layout.addWidget(leLegajo, 0, 1);
    layout.addWidget(lNombre, 1, 0);
    layout.addWidget(leNombre, 1, 1);
    layout.addWidget(lApellido, 2, 0);
    layout.addWidget(leApellido, 2, 1);
    layout.addWidget(pbEnviar, 3, 1);

    setLayout(&layout);
}
