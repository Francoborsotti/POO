#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

int main(int argc, char** argv){
    QApplication a(argc, argv);

    QWidget *ventana = new QWidget;
    ventana->setWindowTitle("Mostrar Imagen");
    ventana->resize(800, 600);

    QImage im("../../fondo_login.png");
    if (im.isNull()) {
        qDebug() << "Imagen nula";
        return -1;
    }

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(im));
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    ventana->setLayout(layout);

    ventana->setVisible( true );

    QTimer::singleShot(5000, &a, &QApplication::quit);

    return a.exec();
}
