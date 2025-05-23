#include "boton.h"
#include <QPainter>
#include <QMouseEvent>

Boton::Boton(QWidget *parent)
    : QWidget(parent), currentColor(Qt::gray) {}

void Boton::colorear(Color color) {
    switch (color) {
    case Azul: currentColor = QColor("#007FFF"); break;
    case Verde: currentColor = QColor("#00CC66"); break;
    case Magenta: currentColor = QColor("#CC00CC"); break;
    }
    update(); // Redibuja el widget
}

void Boton::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), currentColor);
    // Opcional: agregar texto centrado
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, this->objectName());
}

void Boton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        emit signal_clic();
}
