#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

private slots:
    void resultado(QNetworkReply *reply);

private:  
    void peticionTemperature();
    Ui::Ventana *ui;

    QNetworkAccessManager *manager;
};
#endif // VENTANA_H
