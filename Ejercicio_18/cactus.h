#ifndef CACTUS_H
#define CACTUS_H

#include "obstaculo.h"
#include <QColor>

const int CACTUS_ANCHO_MIN = 20;
const int CACTUS_ANCHO_MAX = 40;
const int CACTUS_ALTO_MIN = 30;
const int CACTUS_ALTO_MAX = 60;

class Cactus : public Obstaculo
{
    Q_OBJECT
public:
    explicit Cactus(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private:
    QColor colorCactus;
    int anchoCactus;
    int altoCactus;
};

#endif // CACTUS_H
