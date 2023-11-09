#include "../include/Inventario.hpp"

Inventario::Inventario() {}

bool Inventario::es_tipo_correcto(std::string tipo){
    return (tipo == TIPO_CURATIVO) || (tipo == TIPO_MUNICION ) || (tipo == TIPO_PUZZLE);
}

void Inventario::alta(std::string nombre,std::string tipo) {
    if (es_tipo_correcto(tipo)) {
        if (inventario.tamanio() < LIMITE_ITEM) {
            Item *item = new Item(nombre, tipo);
            inventario.alta(item);
        } else {
            std::cout << "No se pueden cargar más items. El inventario llego a su limite" << std::endl;
        }
    } else {
        std::cout << "Tipo de item incorrecto" << std::endl;
    }
}

void Inventario::baja(std::string item_a_eliminar) {
    bool eliminado = false;
    size_t i = 0;
    while (!eliminado && (i < inventario.tamanio())) {
        if (inventario.elemento(i)->operator==(item_a_eliminar)) {
            Item *item = inventario.elemento(i);
            inventario.baja(i);
            eliminado = true;
            std::cout << "Se eliminó " << item_a_eliminar << " del inventario" << std::endl;
            delete item;
        }
        i++;
    }
    if (!eliminado) {
        std::cout << "No se encontró " << item_a_eliminar << " dentro del inventario" << std::endl;
    }
}

void Inventario::consultar() {
    if (inventario.tamanio() == 0) {
        std::cout << "El inventario esta vacio." << std::endl;
    } else {
        for (size_t i = 0; i < inventario.tamanio(); i++) {
            std::cout << i + (size_t) 1 << ": ";
            inventario.elemento(i)->listar_informacion();
            std::cout << std::endl;
        }
    }
}

void Inventario::guardar() {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cout << "No pudo abrirse el archivo inventario.csv" << std::endl;
        return;
    } else {
        for (size_t i = 0; i < inventario.tamanio(); i++) {
            archivo << *inventario.elemento(i) << std::endl;
        }
        std::cout << "Se guardo el inventario correctamente" << std::endl;
    }
    archivo.close();
}

void Inventario::cargar() {
    std::string linea,nombre,tipo;
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    } else {
        while(getline(archivo,linea)) {
            std::istringstream linea_stream(linea);
            if (std::getline(linea_stream, nombre, DELIMITADOR) && std::getline(linea_stream, tipo)) {
                Item* item = new Item(nombre, tipo);
                inventario.alta(item);
            }
        }
    }
    archivo.close();
}

Inventario::~Inventario() {
    while (!inventario.vacio()) {
        delete inventario.baja();
    }
}
