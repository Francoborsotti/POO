#include "formulario.h"
#include <QMessageBox>

Formulario::Formulario(QWidget *parent) : QWidget(parent) {
    lLegajo = new QLabel("Legajo:");
    lNombre = new QLabel("Nombre:");
    lApellido = new QLabel("Apellido:");
    leLegajo = new QLineEdit;
    leNombre = new QLineEdit;
    leApellido = new QLineEdit;
    pbEnviar = new QPushButton("Enviar");

    randomNumber = QRandomGenerator::global()->bounded(1, 1001);
    randomNumberLabel = new QLabel(QString::number(randomNumber));
    numberInput = new QLineEdit;

    layout.addWidget(lLegajo, 0, 0);
    layout.addWidget(leLegajo, 0, 1);
    layout.addWidget(lNombre, 1, 0);
    layout.addWidget(leNombre, 1, 1);
    layout.addWidget(lApellido, 2, 0);
    layout.addWidget(leApellido, 2, 1);
    layout.addWidget(new QLabel("Número Aleatorio:"), 3, 0);
    layout.addWidget(randomNumberLabel, 3, 1);
    layout.addWidget(new QLabel("Ingrese el Número:"), 4, 0);
    layout.addWidget(numberInput, 4, 1);
    layout.addWidget(pbEnviar, 5, 1);


    setLayout(&layout);

    connect(pbEnviar, &QPushButton::pressed, this, &Formulario::validarFormulario);
    connect(numberInput, SIGNAL(returnPressed()), this, SLOT(validarFormulario()));
}

void Formulario::validarFormulario() {
    if (numberInput->text() == randomNumberLabel->text() && leLegajo->text() != nullptr && leNombre->text() != nullptr && leApellido->text() != nullptr) {
        this->close();
    } else {
        numberInput->clear();
        QMessageBox::warning(this, "Error", "Numero, legajo, nombre o apellido incorrectos");
    }
}
