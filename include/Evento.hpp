#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>

const std::string ACCION_GUARDADO = "GUARDADO";
const std::string ACCION_APERTURA_MAPA = "APERTURA_MAPA";

class Evento {
private:
    std::string accion_ejecutada;
    // Otros atributos asociados a la descripción del evento.

public:
    // Constructor.
    Evento(std::string accion_ejecutada);

    // Constructor default:
    Evento() = default;

    // Pre:
    // Post: Devuelve true si la acción coincide con la ejecutada.
    bool operator==(const std::string& accion);

    // Otros métodos asociados a la clase.
};

#endif
