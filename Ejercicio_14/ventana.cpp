#include "ventana.h"
#include "ui_ventana.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
    , pincelColor(Qt::black)
    , pincelGrossor(3.0)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StaticContents);
    setFocusPolicy(Qt::StrongFocus);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        trazaActual.clear();
        trazaActual.append(event->position());
        update();
    }
}

void Ventana::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        trazaActual.append(event->position());
        update();
    }
}

void Ventana::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !trazaActual.isEmpty()) {
        Trazo nuevoTrazo;
        nuevoTrazo.puntos = trazaActual;
        nuevoTrazo.color = pincelColor;
        trazas.append(nuevoTrazo);
        trazaActual.clear();
        update();
    }
}

void Ventana::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for(const auto& traza : trazas){
        painter.setPen(QPen(traza.color, pincelGrossor, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        for(int i = 1; i < traza.puntos.size(); i++){
            painter.drawLine(traza.puntos[i - 1], traza.puntos[i]);
        }
    }

    painter.setPen(QPen(pincelColor, pincelGrossor, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 1; i < trazaActual.size(); i++){
        painter.drawLine(trazaActual[i - 1], trazaActual[i]);
    }
}

void Ventana::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_R:
        pincelColor = Qt::red;
        break;
    case Qt::Key_G:
        pincelColor = Qt::green;
        break;
    case Qt::Key_B:
        pincelColor = Qt::blue;
        break;
    case Qt::Key_Escape:
        trazas.clear();
        trazaActual.clear();
        update();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Ventana::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
        pincelGrossor = qMin(pincelGrossor + 1.0, 50.0);
    else
        pincelGrossor = qMax(pincelGrossor - 1.0, 1.0);

    event->accept();
}
