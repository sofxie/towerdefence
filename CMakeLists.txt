cmake_minimum_required(VERSION 3.30)
project(towerdefence)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.6.2 REQUIRED COMPONENTS system window graphics)

include_directories(MODELO CONTROLADOR VISTA)

add_executable(towerdefence main.cpp
        VISTA/View.cpp
        VISTA/View.h
        CONTROLADOR/Controler.cpp
        CONTROLADOR/Controler.h
        MODELO/Map.h
        MODELO/Map.cpp
        VISTA/VisualEnemy.h
        MODELO/Enemigos/Wave.cpp
        MODELO/Enemigos/Enemy.cpp
        MODELO/Enemigos/EnemyController.h
        MODELO/Torre/Torre_Arco.cpp
        MODELO/Torre/Torre_Arco.h
        MODELO/Torre/Torre_Artillero.cpp
        MODELO/Torre/Torre_Artillero.h
        MODELO/Enemigos/EnemyController.cpp
        MODELO/Torre/Torre_Mago.cpp)
target_link_libraries(towerdefence sfml-system sfml-window sfml-graphics)

file(COPY ${CMAKE_SOURCE_DIR}/Imagenes DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Font DESTINATION ${CMAKE_BINARY_DIR})