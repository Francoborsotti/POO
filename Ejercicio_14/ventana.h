#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QColor>

struct Trazo
{
    QVector<QPointF> puntos;
    QColor color;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class Ventana;
}
QT_END_NAMESPACE

class Ventana : public QWidget
{
    Q_OBJECT

public:
    Ventana(QWidget *parent = nullptr);
    ~Ventana();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::Ventana *ui;

    QVector<Trazo> trazas;
    QVector <QPointF> trazaActual;
    QColor pincelColor;
    qreal pincelGrossor;
};
#endif // VENTANA_H
