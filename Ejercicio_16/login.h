#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <admindb.h>

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
    void setUsuario();

private:
    Ui::Login *ui;
    Admindb * adminDB;

private slots:
    void slot_validarUsuario();
    void slot_agregarUsuario();
};
#endif // LOGIN_H
