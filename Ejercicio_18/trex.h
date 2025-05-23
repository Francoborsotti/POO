#ifndef TREX_H
#define TREX_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QColor>

const int TREX_ANCHO_BASE = 30;
const int TREX_ALTO_BASE = 50;
const int TREX_ALTO_AGACHADO = 25;

const int GRAVEDAD_TREX = 1;
const int FUERZA_SALTO_INICIAL_TREX = -17;

class TRex : public QWidget
{
    Q_OBJECT

public:
    enum Estado { Corriendo, Saltando, Agachado };

    explicit TRex(QWidget *parent = nullptr);
    ~TRex();

    void saltar();
    void agacharse();
    void dejarDeAgacharse();
    void actualizarPosicion();
    QRect getRect() const;
    void setAlturaSuelo(int altura);
    void resetear();

    void setVelocidadX(int vel);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Estado estadoActual;
    QColor colorTRex;

    int velocidadY;
    int alturaSuelo;
    int posXInicial, posYInicial;
    int velocidadX;

    int anchoActual;
    int altoActual;

    void actualizarDimensiones();
};

#endif // TREX_H
