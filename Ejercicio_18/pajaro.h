#ifndef PAJARO_H
#define PAJARO_H

#include "obstaculo.h"
#include <QTimer>
#include <QColor>

const int PAJARO_RADIO_MIN = 10;
const int PAJARO_RADIO_MAX = 15;

class Pajaro : public Obstaculo
{
    Q_OBJECT
public:
    explicit Pajaro(QWidget *parent = nullptr);
    ~Pajaro();

    void paintEvent(QPaintEvent *event) override;
    void iniciarMovimiento(int velocidad);
    void detenerMovimiento();

private:
    QTimer *timerMovimientoPropio;
    QColor colorPajaro;
    int radioPajaro;
    int velocidadHorizontal;

private slots:
    void slotMoverIzquierda();
};

#endif // PAJARO_H
