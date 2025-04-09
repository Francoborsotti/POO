#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>

namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();

private:
    Ui::Ventana *ui;

    QNetworkAccessManager manager;
    QImage image;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void slot_descargaFinalizada(QNetworkReply * reply);
};

#endif // VENTANA_H
