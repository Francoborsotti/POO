#ifndef INSTRUMENTO_H
#define INSTRUMENTO_H

#include <QString>
#include <QDebug>

class Instrumento
{
public:
    Instrumento(const QString &marca = "Yamaha");
    virtual ~Instrumento();

    virtual void sonar() const = 0;

    virtual void verlo() const;

    QString getMarca() const;
    void setMarca(const QString &marca);

protected:
    QString m_marca;
};

#endif
