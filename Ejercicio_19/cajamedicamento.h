#ifndef CAJAMEDICAMENTO_H
#define CAJAMEDICAMENTO_H

#include <QWidget>

class CajaMedicamento : public QWidget
{
    Q_OBJECT
public:
    CajaMedicamento(float dosis);
    CajaMedicamento(int id, float dosis);

    CajaMedicamento operator+(const CajaMedicamento &otra) const;
    bool operator==(const CajaMedicamento &otra) const;

    QString toString() const;

    int getId() const;
    float getDosisTotales() const;

private:
    int id;
    float dosisTotales;

signals:
};

#endif // CAJAMEDICAMENTO_H
