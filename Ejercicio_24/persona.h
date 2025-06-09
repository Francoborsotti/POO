#ifndef PERSONA_H
#define PERSONA_H

#include <QString> // Para el atributo nombre
#include <QDebug>  // Para usar qDebug() en el método mostrar()

class Persona
{
public:
    // Constructor que recibe el nombre
    explicit Persona(const QString &nombre);

    // Destructor (útil para decrementar el contador si una persona es eliminada)
    ~Persona();

    // Método para imprimir el nombre de la persona
    void mostrar() const;

    // Miembro de función estático:
    // Devuelve el total de personas creadas. Puede ser llamado sin una instancia.
    static int totalPersonas();

private:
    QString m_nombre; // Atributo privado: el nombre de la persona (usamos m_ para miembros)

    // Miembro de datos estático:
    // Almacena el conteo de personas. Es compartido por todas las instancias.
    static int s_contadorPersonas; // Usamos s_ para variables estáticas
};

#endif // PERSONA_H
