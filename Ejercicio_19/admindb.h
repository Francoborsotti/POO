#ifndef ADMINDB_H
#define ADMINDB_H

#include <QSqlDatabase>
#include <QList>
#include "cajamedicamento.h"

class AdminDB
{
public:
    static AdminDB* getInstance();

    bool conectar(const QString& nombreArchivo = "medicamentos.sqlite");
    void desconectar();

    bool insertarCaja(float dosis);
    QList<CajaMedicamento> obtenerTodas();
    float obtenerTotalDosisActuales();
    bool reemplazarDosCajasConSuma(int idCaja1, int idCaja2, float dosisSuma);
    QSqlError getLastError(); // Para obtener información de error de la BD

private:
    AdminDB();
    ~AdminDB();
    AdminDB(const AdminDB&) = delete;
    AdminDB& operator=(const AdminDB&) = delete;

    static AdminDB* instancia;
    QSqlDatabase db;

    bool crearTablaSiNoExiste();
    const float LIMITE_MAXIMO_DOSIS_TOTALES = 1000.0f;
};

#endif // ADMINDB_H
