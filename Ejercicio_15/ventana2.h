#ifndef VENTANA2_H
#define VENTANA2_H

#include <QWidget>

#include "admindb.h"

namespace Ui {
class Ventana2;
}

class Ventana2 : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana2(QWidget *parent = nullptr);
    ~Ventana2();
    void setUsuarioActual(const QString &usuario);
    void mostrarUltimosUsuarios();

private:
    Ui::Ventana2 *ui;
    AdminDB * adminDB;
    QString usuarioActual;
};

#endif // VENTANA2_H
