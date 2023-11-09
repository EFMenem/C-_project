#ifndef LISTAS_TESTS_DESTINO_H
#define LISTAS_TESTS_DESTINO_H
#include "Cola.hpp"
#include <string>
#include "Evento.hpp"

class Destino {
private:
    Cola<Evento*> destino;
    std::string perfil_jugador;

    //PRE: --
    //POST: modifica el perfil del jugador a desorientado
    void personaje_desorientado();

    //PRE: --
    //POST: modifica el perfil del jugador a asustado
    void personaje_asustado();

    //PRE: --
    //POST: modifica el perfil del jugador a precavido
    void personaje_precavido();

    //PRE:
    //POST: modifica el perfil del jugador a no determinado
    void personaje_no_determinado();

    //PRE: --
    //POST: devuelve verdadero si evento esta en el conjunto {GUARDADO,APERTURA_MAPA}
    bool evento_valido(Evento* evento);


public:
    //Constructor
    Destino();

    //PRE:--
    //POST: devuelve el perfil del jugador.
    std::string obtener_perfil();

    //PRE:--
    //POST: define el perfil del jugador.
    std::string definir_perfil();

    //PRE:--
    //POST:imprime por pantalla el suceso relacionado al perfil.
    void obtener_suceso();

    //PRE: --
    //POST: agrega a la cola un evento.
    void alta(std::string evento);

    //PRE:--
    //POST: devuelve el destino ya definido
    void destino_definido();

    //Destructor
    ~Destino();
};

#endif
