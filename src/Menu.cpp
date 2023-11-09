#include "../include/Menu.hpp"
#include <iostream>
Menu::Menu(){}

void Menu::opciones_destino() {
    std::cout << "DESTINO"
                 "\n--------------------------------------------------------------------------------\n"
                 "Opciones:\n"
                 "-AGREGAR_EVENTO: agrega un evento al destino.\n"
                 "-DEFINIR_DESTINO. define el destino del jugador.\n"
                 "-MOSTRAR_SUCESO. muestra la accion tomada en base al perfil del jugador.\n"
                 "-VOLVER. Vuelve al menu anterior.\n"
                 "--------------------------------------------------------------------------------\n";
}

bool Menu::comando_valido_menu(std::string comando) {
    return (comando == "DESTINO") || (comando  == "INVENTARIO") || (comando == "SALIR");
}

bool Menu::comando_valido_destino(std::string comando) {
    return (comando == AGREGAR) || (comando == SUCESO) || (comando == VOLVER) || (comando == DEFINIR);
}

void Menu::acciones_destino() {
    std::string accion;
    bool desea_salir = false;
    while(!desea_salir) {
        std::cout << "¿Que accion desea realizar sobre el Destino? :";
        getline(std::cin >> std::ws,accion);
        if (comando_valido_destino(accion)) {
            if (accion == AGREGAR) {
                std::cout << "Evento experimentado (APERTURA_MAPA o GUARDADO): ";
                getline(std::cin >> std::ws, accion);
                destino.alta(accion);
            } else if (accion == DEFINIR) {
                destino.destino_definido();
            } else if (accion == SUCESO) {
                destino.obtener_suceso();
            } else {
                desea_salir = true;
            }
        } else {
            std::cout << "Comando erroneo. Por favor ingrese uno correcto " << std::endl;
        }
        if (!desea_salir) {
            opciones_destino();
        }
    }
}

void Menu::menu_destino() {
    opciones_destino();
    acciones_destino();
}

void Menu::manejar_menu() {
    std::string comando;
    bool desea_salir = false;
    while (!desea_salir) {
        std::cout << "Las opciones válidas son INVENTARIO o DESTINO\nOperar sobre Inventario o Destino: ";
        getline(std::cin >> std::ws, comando);
        if (comando_valido_menu(comando)) {
            if (comando == "DESTINO") {
                menu_destino();
            } else if (comando == "INVENTARIO") {
                menu_inventario();
            } else {
                desea_salir = true;
            }
        } else {
            std::cout << "Comando erroneo. Por favor ingrese uno correcto." << std::endl;
        }
    }
}

void Menu::acciones_inventario() {
    std::string item,nombre,tipo,comando;
    std::cout << "Accion sobre el inventario: ";
    getline(std::cin >> std::ws,comando);
    inventario.cargar();
    while(comando != "SALIR") {
        if (!comando_valido_inventario(comando)) {
            std::cout << "Ingreso un comando erroneo por favor ingrese de nuevo:" << std::endl;
        } else if (comando == "ALTA") {
            std::cout << "Ingrese un nombre : ";
            getline(std::cin >> std::ws, nombre);
            std::cout << "Ingrese un tipo(PUZZLE, MUNICION o CURATIVO): ";
            getline(std::cin >> std::ws , tipo);
            inventario.alta(nombre,tipo);
        } else if (comando == "CONSULTA") {
            inventario.consultar();
        } else if (comando == "BAJA") {
            std::cout << "Indique el ítem a eliminar : ";
            getline(std::cin, item);
            inventario.baja(item);
        } else if (comando == "GUARDAR") {
            inventario.guardar();
        }
        opciones_inventario();
        std::cout << "Accion sobre el inventario : ";
        getline(std::cin ,comando);
    }
    inventario.guardar();
}

bool Menu::comando_valido_inventario(std::string comando) {
    return (comando == "ALTA") || (comando == "CONSULTA") || (comando == "GUARDAR") || (comando == "SALIR")  || (comando == "BAJA");
}

void Menu::opciones_inventario() {
    std::cout << "INVENTARIO\n--------------------------------------------------------------------\n";
    std::cout << "Opcion:\n-'ALTA' carga de a un item en el inventario\n-'BAJA' da de baja de a un item del inventario\n";
    std::cout << "-'GUARDAR' guarda los items en un archivo.csv\n";
    std::cout << "-'CONSULTA' consulta por pantalla los items del inventario\n-'SALIR' para salir del inventario\n";
    std::cout << "--------------------------------------------------------------------\n";
}

void Menu::menu_inventario() {
    opciones_inventario();
    acciones_inventario();
}
