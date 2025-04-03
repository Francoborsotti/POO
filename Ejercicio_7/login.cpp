#include "login.h"
#include "formulario.h"
#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent) {
    lUsuario = new QLabel("Usuario:");
    lClave = new QLabel("Clave:");
    leUsuario = new QLineEdit;
    leClave = new QLineEdit;
    leClave->setEchoMode(QLineEdit::Password);
    pbIngresar = new QPushButton("Ingresar");

    layout.addWidget(lUsuario, 0, 0);
    layout.addWidget(leUsuario, 0, 1);
    layout.addWidget(lClave, 1, 0);
    layout.addWidget(leClave, 1, 1);
    layout.addWidget(pbIngresar, 2, 1);

    setLayout(&layout);

    connect(pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validar()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar()));
}

void Login::slot_validar() {
    if (leUsuario->text() == "admin" && leClave->text() == "1111") {
        Formulario *formulario = new Formulario;
        formulario->show();
        this->close();
    } else {
        leClave->clear();
        QMessageBox::warning(this, "Clave Incorrecta", "La clave ingresada es incorrecta.");
    }
}
