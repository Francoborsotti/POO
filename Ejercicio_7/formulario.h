#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QRandomGenerator>

class Formulario : public QWidget {
    Q_OBJECT

public:
    Formulario(QWidget *parent = nullptr);

private slots:
    void validarFormulario();

private:
    QLabel *lLegajo;
    QLabel *lNombre;
    QLabel *lApellido;
    QLineEdit *leLegajo;
    QLineEdit *leNombre;
    QLineEdit *leApellido;
    QPushButton *pbEnviar;
    QGridLayout layout;

    QLabel *randomNumberLabel;
    QLineEdit *numberInput;
    int randomNumber;
};

#endif // FORMULARIO_H
