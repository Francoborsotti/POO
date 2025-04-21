#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QColor>

struct Trazo
{
    QVector<QPointF> puntos;
    QColor color;
};

class Pintura : public QWidget{
    Q_OBJECT

public:
    explicit Pintura(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QVector<Trazo> trazas;
    QVector <QPointF> trazaActual;
    QColor pincelColor;
    qreal pincelGrossor;

};

#endif // PINTURA_H
