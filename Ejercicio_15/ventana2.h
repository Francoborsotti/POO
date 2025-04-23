#ifndef VENTANA2_H
#define VENTANA2_H

#include <QWidget>

namespace Ui {
class Ventana2;
}

class Ventana2 : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana2(QWidget *parent = nullptr);
    ~Ventana2();

private:
    Ui::Ventana2 *ui;
};

#endif // VENTANA2_H
