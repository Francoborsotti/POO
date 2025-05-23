#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QWidget>
#include <QPainter>
#include <QRect>
#include <QPoint>

class Obstaculo : public QWidget
{
    Q_OBJECT

public:
    explicit Obstaculo(QWidget *parent = nullptr);
    virtual ~Obstaculo();

    QRect getRect() const;
    void setPosicion(int x, int y);
    QPoint getPosicion() const;

    virtual void paintEvent(QPaintEvent *event) override = 0;

protected:
    QPoint posicion;
};

#endif // OBSTACULO_H
