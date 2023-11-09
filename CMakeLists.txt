cmake_minimum_required(VERSION 3.22)
project(ayp2_plantilla_tp2_2c2023)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Werror -Wconversion)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CXXFLAGS "-Wall -Werror -Wconversion -std=c++20")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

include_directories(include)
include_directories(src)

add_executable(ayp2_plantilla_tp2_2c2023
        main.cpp
        src/Evento.cpp
        src/Item.cpp
        src/Menu.cpp
        src/Inventario.cpp
        src/Destino.cpp

        # Otros archivos .cpp, de la forma src/Ejemplo.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")