#ifndef ELECTRICO_H
#define ELECTRICO_H

#include <QDebug>

class Electrico
{
public:
    Electrico(int voltaje = 220);
    virtual ~Electrico();

    int getVoltaje() const;
    void setVoltaje(int voltaje);

protected:
    int m_voltaje;
};

#endif
