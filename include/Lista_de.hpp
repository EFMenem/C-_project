#ifndef LISTA_DE_HPP
#define LISTA_DE_HPP

#include <exception>
#include <cstdlib>
#include "Nodo_de.hpp"
#include <cmath>

class Lista_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la lista.
    // Usar de la forma "throw lista_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw Lista_exception();
    //     }
};

template<typename T>
class Lista_de {
private:
    Nodo_de<T>* primer_nodo;
    Nodo_de<T>* ultimo_nodo;
    Nodo_de<T>* cursor;
    // Nota: pueden no utilizar el índice. Estado inicial / no válido = -1.
    // La lista es 0-indexed.
    int indice_cursor;
    size_t cantidad_datos;

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve un puntero al nodo asociado al índice deseado.
    Nodo_de<T>* obtener_nodo(size_t indice);

    // Pre: --
    // Post: devuelve un puntero iterando desde el punto de partida mas cerca pero siempre de menor al mayor.
    Nodo_de<T>* iterar_hacia_adelante(size_t indice);

    // Pre: --
    // Post: devuelve un puntero iterando desde el punto de partida mas cerca pero siempre de mayor al menor.
    Nodo_de<T>* iterar_hacia_atras(size_t indice);

public:
    // Constructor.
    Lista_de();

    // Pre: -
    // Post: Agrega el dato al final de la lista.
    void alta(T dato);

    // Pre: La lista no puede estar vacía.
    // Post: Elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja();

    // Pre: El índice debe ser menor o igual que la cantidad de datos.
    // Post: Agrega el dato antes del dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos, simplemente agrega al final.
    void alta(T dato, size_t indice);

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Elimina el dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos - 1, simplemente elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja(size_t indice);

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el primer dato en la lista.
    T primero();

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el último dato en la lista.
    T ultimo();

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve el dato en la posición deseada.
    T elemento(size_t indice);

    // Pre: -
    // Post: Devuelve true si se puede avanzar (esto es, que el cursor no sea nullptr).
    bool puede_avanzar();

    // Pre: Se debe poder avanzar.
    // Post: Devuelve el dato del cursor actual y luego lo mueve una posición en la dirección deseada.
    T avanzar(bool siguiente);

    // Pre: -
    // Post: Reinicia el cursor al principio o al final, según lo indicado.
    // Si la lista está vacía, se reinicia el cursor al estado inicial
    // (esto es, cursor = nullptr e indice_cursor = -1).
    void reiniciar_cursor(bool principio);

    // Pre: -
    // Post: Devuelve la cantidad de datos de la lista.
    size_t tamanio();

    // Pre: -
    // Post: Devuelve true si la lista esta vacía (es decir, si no hay datos).
    bool vacio();

    // El constructor de copia está deshabilitado.
    Lista_de(const Lista_de& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Lista_de& l) = delete;

    // Destructor.
    ~Lista_de();
};

template <typename T>
Lista_de<T>::Lista_de() {
    primer_nodo = nullptr;
    ultimo_nodo = nullptr;
    cursor = nullptr;
    indice_cursor = -1;
    cantidad_datos = 0;
}

template <typename T>
Nodo_de<T>* Lista_de<T>::iterar_hacia_adelante(size_t indice) {
    int primer_elemento = 0;
    Nodo_de<T>* nodo_deseado;
    if (abs(static_cast<int> (indice) - indice_cursor) < abs(static_cast<int> (indice) - primer_elemento)) {
        nodo_deseado = cursor;
        for (int i = indice_cursor; i < indice; i++) {
                nodo_deseado = nodo_deseado->obtener_siguiente();
        }
    } else {
        nodo_deseado = primer_nodo;
        for (size_t i = 0; i < indice; i++) {
            nodo_deseado = nodo_deseado->obtener_siguiente();
        }
    }
    return nodo_deseado;
}

template <typename T>
Nodo_de<T>* Lista_de<T>::iterar_hacia_atras(size_t indice) {
    int primer_elemento = 0;
    Nodo_de<T>* nodo_deseado;
    if (abs(static_cast<int> (indice) - indice_cursor) < abs(static_cast<int> (indice) - primer_elemento)) {
        nodo_deseado = cursor;
        for (int i = indice_cursor; i > (int) indice; i--) {
            nodo_deseado = nodo_deseado->obtener_anterior();
        }
    } else {
        nodo_deseado = iterar_hacia_adelante(indice);
    }
    return nodo_deseado;
}


template <typename T>
Nodo_de<T>* Lista_de<T>::obtener_nodo(size_t indice) {
    if (indice >= tamanio() ) {
        throw Lista_exception();
    }
    Nodo_de<T>* nodo_solicitado;
    if( (int) indice > indice_cursor) {
        nodo_solicitado = iterar_hacia_adelante(indice);

    } else if ( (int) indice == indice_cursor) {
        nodo_solicitado = cursor;
    } else {
        nodo_solicitado = iterar_hacia_atras(indice);
    }
    indice_cursor = (int) indice;
    cursor = nodo_solicitado;
    return nodo_solicitado;
}

template <typename T>
void  Lista_de<T>::alta(T dato) {
    Nodo_de<T>* nuevo = new Nodo_de<T>(dato);
    if (vacio()) {
        primer_nodo = nuevo;
        ultimo_nodo = nuevo;
    } else {
        nuevo->cambiar_anterior(ultimo_nodo);
        ultimo_nodo->cambiar_siguiente(nuevo);
        ultimo_nodo = nuevo;
    }
    cantidad_datos++;
    reiniciar_cursor(true);
}

template <typename T>
T Lista_de<T>::baja() {
    if (vacio()) {
        throw Lista_exception();
    }
    T dato_a_bajar = ultimo_nodo->obtener_dato();
    Nodo_de<T> *anterior = ultimo_nodo->obtener_anterior();
    if (tamanio() > 1) {
        anterior->cambiar_siguiente(nullptr);
        if (cursor == ultimo_nodo) {
            cursor = anterior;
        }
    } else {
        primer_nodo = nullptr;
    }
    delete ultimo_nodo;

    ultimo_nodo = anterior;
    cantidad_datos--;
    reiniciar_cursor(true);
    return dato_a_bajar;

}

template <typename T>
void Lista_de<T>::alta(T dato, size_t indice) {
    if (indice > tamanio()) {
        throw Lista_exception();
    } else {
        if (indice == tamanio()) {
            alta(dato);
            return;
        } else {
            if (indice == 0) {
                Nodo_de<T>* nuevo = new Nodo_de<T>(dato);
                nuevo->cambiar_siguiente(primer_nodo);
                primer_nodo->cambiar_anterior(nuevo);
                if (cursor == primer_nodo) {
                    cursor = nuevo;
                }
                primer_nodo = nuevo;

            } else {
                Nodo_de<T>* anterior = obtener_nodo(indice)->obtener_anterior();
                Nodo_de<T> *siguiente = obtener_nodo(indice);
                Nodo_de<T> *nuevo = new Nodo_de<T>(dato, anterior, siguiente);
                anterior->cambiar_siguiente(nuevo);
                siguiente->cambiar_anterior(nuevo);
                if (cursor == siguiente) {
                    cursor = nuevo;
                }
            }
        }
    }
    cantidad_datos++;
}

template <typename T>
T Lista_de<T>::baja(size_t indice) {
    if (indice >= tamanio()) {
        throw Lista_exception();
    }
    if (indice == cantidad_datos - 1) {
        return baja();
    } else {
        Nodo_de<T>* nodo_a_eliminar = obtener_nodo(indice);
        T dato = nodo_a_eliminar->obtener_dato();
        if (indice == 0) {
            Nodo_de<T>* siguiente = nodo_a_eliminar->obtener_siguiente();
            siguiente->cambiar_anterior(nullptr);
            if(cursor == primer_nodo) {
                cursor = siguiente;
            }
            primer_nodo = siguiente;

        } else {
            Nodo_de<T>* anterior = nodo_a_eliminar->obtener_anterior();
            Nodo_de<T>* siguiente = nodo_a_eliminar->obtener_siguiente();
            anterior->cambiar_siguiente(siguiente);
            siguiente->cambiar_anterior(anterior);
            if (cursor == nodo_a_eliminar) {
                cursor = siguiente;
            }
        }
        delete nodo_a_eliminar;
        cantidad_datos--;
        return dato;
    }
}

template <typename T>
T Lista_de<T>::primero() {
    if (vacio()) {
        throw Lista_exception();
    } else {
        return primer_nodo->obtener_dato();
    }
}

template <typename T>
T Lista_de<T>::ultimo() {
    if(vacio()) {
        throw Lista_exception();
    } else {
        return ultimo_nodo->obtener_dato();
    }
}

template <typename T>
T Lista_de<T>::elemento(size_t indice) {
    if ( indice >= tamanio() ) {
        throw Lista_exception();
    }
    return obtener_nodo(indice)->obtener_dato();
}

template <typename T>
bool Lista_de<T>::puede_avanzar() {
    return cursor != nullptr;
}

template <typename T>
T Lista_de<T>::avanzar(bool siguiente) {
    if (!puede_avanzar()) {
        throw Lista_exception();
    }
    T dato = cursor->obtener_dato();
    if (siguiente) {
        cursor = cursor->obtener_siguiente();
    } else {
        cursor = cursor->obtener_anterior();
    }
    return dato;
}

template <typename T>
void Lista_de<T>::reiniciar_cursor(bool principio) {
    if (vacio()) {
        cursor = nullptr;
        indice_cursor = -1;
    } else if (principio) {
        cursor = primer_nodo;
        indice_cursor = 0;
    } else if (!principio) {
        indice_cursor = (int) cantidad_datos - 1;
        cursor = ultimo_nodo;
    }
}

template <typename T>
size_t Lista_de<T>::tamanio(){
    return cantidad_datos;
}

template <typename T>
bool Lista_de<T>::vacio() {
    return (cantidad_datos == 0);
}

template <typename T>
Lista_de<T>::~Lista_de() {
    while(!vacio()) {
        baja();
    }
}

#endif