#ifndef ADMINDB_H
#define ADMINDB_H

#include <QWidget>

#include <QSqlDatabase>
#include <QString>

class Admindb : public QWidget
{
    Q_OBJECT
public:
    explicit Admindb(QWidget *parent = nullptr);

    bool conectar(QString archivoSqlite);
    QSqlDatabase getDB();

    bool validarUsuario(QString tabla, QString usuario, QString clave);
    QString setUsuariodb();
    bool agregarUsuario(QString tabla, QString usuario, QString clave);

private:
    QSqlDatabase db;

signals:
};

#endif // ADMINDB_H
