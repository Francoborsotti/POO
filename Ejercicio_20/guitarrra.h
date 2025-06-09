#ifndef GUITARRA_H
#define GUITARRA_H

#include "instrumento.h"

class Guitarra : public Instrumento
{
public:
    Guitarra(int cuerdas = 6, const QString &marca = "Yamaha");

    void sonar() const override;

    int getCuerdas() const;
    void setCuerdas(int cuerdas);

private:
    int m_cuerdas;
};

#endif
