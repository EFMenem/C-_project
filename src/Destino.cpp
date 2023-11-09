#include "../include/Destino.hpp"
#include <iostream>

Destino::Destino() {
    perfil_jugador = "";
}
void Destino::personaje_desorientado() {
    perfil_jugador = "desorientado";
}

void Destino::personaje_precavido() {
    perfil_jugador = "precavido";
}
void Destino::personaje_asustado() {
    perfil_jugador = "asustado";
}

void Destino::personaje_no_determinado() {
    perfil_jugador = "no determinado";
}

bool Destino::evento_valido(Evento* evento){
    return (*evento == ACCION_APERTURA_MAPA) || (*evento == ACCION_GUARDADO);
}

std::string Destino::obtener_perfil() {
    return perfil_jugador;
}

void Destino::obtener_suceso() {
    if(obtener_perfil() == "no determinado") {
        std::cout << "Comportamiento aún no definido"  << std::endl;
    } else if (obtener_perfil() == "asustado") {
        std::cout << "Evento Pyramid Head adelantado" << std::endl;
    } else if (obtener_perfil() == "precavido") {
        std::cout << "Aumento en la cantidad de enemigos" << std::endl;
    } else {
        std::cout << "Aumento de factores ambientales" << std::endl;
    }
}

void Destino::destino_definido() {
    definir_perfil();
    std::cout << "Destino definido. El jugador es : " << obtener_perfil() << "." << std::endl;
}

void Destino::alta(std::string accion) {
    Evento* evento = new Evento(accion);
    if (evento_valido(evento)) {
        destino.alta(evento);
    } else {
        std::cout << "Evento erroneo, no pudo guardarse. " << std::endl;
        delete evento;
    }
}

std::string Destino::definir_perfil() {
    int aperturas_mapa = 0, guardados = 0;
    perfil_jugador = "";
    while (guardados < 8 && (!destino.vacio())) {
        Evento * dato_a_eliminar = destino.baja();
        if (*dato_a_eliminar == ACCION_APERTURA_MAPA) {
            aperturas_mapa++;
        } else {
            guardados++;
        }
        if (guardados >= 8) {
            personaje_asustado();
        } else if (aperturas_mapa > guardados && aperturas_mapa > 5 && guardados < 8) {
            personaje_desorientado();
        } else if (guardados > aperturas_mapa && guardados >= 5 && guardados < 8) {
            personaje_precavido();
        }
        delete dato_a_eliminar;
    }
    if(obtener_perfil() == "") {
        personaje_no_determinado();
    }
    return perfil_jugador;
}

Destino::~Destino() {
    while(!destino.vacio()) {
        delete destino.baja();
    }

}
