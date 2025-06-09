#include "persona.h"

// Definición e inicialización del miembro de datos estático.
// Esto debe hacerse *fuera* de la clase en un archivo .cpp.
// Solo se inicializa una vez.
int Persona::s_contadorPersonas = 0;

// Constructor de la clase Persona
Persona::Persona(const QString &nombre) : m_nombre(nombre)
{
    // Cada vez que se crea una nueva instancia de Persona, incrementamos el contador estático.
    s_contadorPersonas++;
    qDebug() << "Persona creada:" << m_nombre << "-> Total de personas ahora:" << s_contadorPersonas;
}

// Destructor de la clase Persona
Persona::~Persona()
{
    // Cada vez que una instancia de Persona es destruida, decrementamos el contador estático.
    s_contadorPersonas--;
    qDebug() << "Persona destruida:" << m_nombre << "-> Total de personas restantes:" << s_contadorPersonas;
}


// Implementación del método mostrar
void Persona::mostrar() const
{
    qDebug() << "Nombre: " << m_nombre;
}

// Implementación del método estático totalPersonas
// No necesita una instancia de Persona para ser llamado.
int Persona::totalPersonas()
{
    return s_contadorPersonas;
}
