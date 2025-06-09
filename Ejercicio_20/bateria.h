#ifndef BATERIA_H
#define BATERIA_H

#include "instrumento.h"

class Bateria : public Instrumento
{
public:
    Bateria(int tambores = 5, const QString &marca = "Yamaha");

    void sonar() const override;

    int getTambores() const;
    void setTambores(int tambores);

private:
    int m_tambores;
};

#endif // BATERIA_H
