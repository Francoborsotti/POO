#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include "admindbmedicamentos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void agregarCaja();
    void sumarCajas();
    void compararCajas();

private:
    Ui::Widget *ui;
    AdminDB *adminBD;
};

#endif // WIDGET_H
