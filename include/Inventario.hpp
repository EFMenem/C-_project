#ifndef _INVENTARIO_HPP
#define _INVENTARIO_HPP
#include "Item.hpp"
#include "Lista_de.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

const std::string ruta = "inventario.csv";
const size_t LIMITE_ITEM = 15;
const char DELIMITADOR = ',';

class Inventario {
private:
    Lista_de<Item*> inventario;

    //PRE:--
    //POST: devuelve verdadero si el tipo de item es correcto.
    bool es_tipo_correcto(std::string tipo);

public:
    //Constructor
    Inventario();

    //PRE:--
    //POST: agrega el item recogido por el jugador al inventario
    void alta(std::string nombre,std::string tipo);

    //PRE:--
    //POST: elimina un item del inventario
    void baja(std::string item_a_eliminar);

    //PRE:--
    //POST: Imprime por pantalla los items en el inventario.
    void consultar();

    //PRE:--
    //POST: carga la informacion del archivo .csv en el inventario.
    void cargar();

    //PRE:--
    //POST: guarda en el archivo .csv los datos del inventario.
    void guardar();

    //Destructor
    ~Inventario();
};
#endif
