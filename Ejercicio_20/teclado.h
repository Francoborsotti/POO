#ifndef TECLADO_H
#define TECLADO_H

#include "instrumento.h"
#include "electrico.h"

class Teclado : public Instrumento, public Electrico
{
public:
    Teclado(int teclas = 61, const QString &marca = "Yamaha", int voltaje = 220);
    ~Teclado();

    void sonar() const override;
    void verlo() const override;

    int getTeclas() const;
    void setTeclas(int teclas);

private:
    int m_teclas;
};

#endif // TECLADO_H
