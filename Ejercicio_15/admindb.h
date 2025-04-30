#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>

#include <QSqlDatabase>
#include <QString>


class AdminDB : public QObject
{
    Q_OBJECT
public:
    explicit AdminDB(QObject *parent = nullptr);

    bool conectar(QString archivoSqlite);
    QSqlDatabase getDB();

    bool validarUsuario(QString tabla, QString usuario, QString clave);

    void setUsuarioActual(const QString &usuario);
    QString getUsuarioActual() const;

private:
    QSqlDatabase db;
    QString usuarioActual;

signals:
};

#endif // ADMINDB_H
