#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>


QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;

    QNetworkAccessManager manager;
    QImage image;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void slot_descargaFinalizada(QNetworkReply * reply);
    void slot_validarUsuario();
};
#endif // LOGIN_H
