#ifndef LISTAS_TESTS_MENU_H
#define LISTAS_TESTS_MENU_H

#include "Destino.hpp"
#include "Inventario.hpp"

const std::string AGREGAR = "AGREGAR_EVENTO";
const std::string DEFINIR = "DEFINIR_DESTINO";
const std::string SUCESO = "MOSTRAR_SUCESO";
const std::string VOLVER = "VOLVER";
class Menu {
private:
    Destino destino;
    Inventario inventario;

    //PRE:--
    //POST: devuelve verdaderi si comando esta en el conjunto {AGREGAR_EVENTO,DEFINIR_DESTINO,MOSTRAR_SUCESO,VOLVER}
    bool comando_valido_destino(std::string comando);

    //PRE:--
    //POST: devuelve verdadero si el comando esta en el conjunto {DESTINO,INVENTARIO}
    bool comando_valido_menu(std::string comando);

    //PRE:--
    //POST: verifica que el comando pertenezca al conjunto {ALTA,BAJA,CONSULTA,CARGAR,GUARDAR,SALIR}
    bool comando_valido_inventario(std::string comando);

public:
    //constructor
    Menu();

    //PRE:--
    //POST: imprime por pantalla las opciones para trabajar con el destino
    void opciones_destino();

    //PRE:--
    //POST: se efectuan las acciones sobre la clase destino.
    void acciones_destino();

    //PRE:--
    //POST: dependiendo la eleccion, se utiliza el inventario o el destino
    void manejar_menu();

    //PRE:--
    //POST: ejecuta los metodos del menu para usar la clase destino.
    void menu_destino();

    //PRE:--
    //POST:imprime por pantalla el menu del inventario
    void mostrar_inventario();

    //PRE:--
    //POST: se imprime por pantalla la ejecucion de los diferentes metodos del inventario.
    void acciones_inventario();

    //PRE:--
    //POST:imprime por pantalla un menu con los comandos del inventario
    void opciones_inventario();

    //PRE:--
    //POST: ejecuta los metodos del menu para usar la clase inventario.
    void menu_inventario();

};

#endif
