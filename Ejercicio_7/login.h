#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Login : public QWidget {
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);

private slots:
    void slot_validar();

private:
    QLabel *lUsuario;
    QLabel *lClave;
    QLineEdit *leUsuario;
    QLineEdit *leClave;
    QPushButton *pbIngresar;
    QGridLayout layout;
};

#endif // LOGIN_H
