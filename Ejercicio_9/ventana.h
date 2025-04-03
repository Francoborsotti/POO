#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>

class Ventana : public QWidget {
    Q_OBJECT

public:
    Ventana();

private:
    QNetworkAccessManager manager;
    QImage image;

protected:
    void paintEvent( QPaintEvent * );

private slots:
    void slot_descargaFinalizada(QNetworkReply * reply);
};

#endif
