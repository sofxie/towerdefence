#ifndef CONTROLER_H
#define CONTROLER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "View.h"
#include "VisualEnemy.h"
#include "Wave.h"


class Controler {
public:
    Controler(); // Constructor
    void run(); // Bucle del juego
    using Pair = std::pair<int, int>;


private:
    void events(); // Funcion que maneja controles del juego
    void update(); // Actualizar mapa
    void render(); // Proyectar en la interfaz
    void crearOleada(); // Crear oleada de enemigos

    sf::RenderWindow window;
    Map mapa; // Incluir clases
    View vista;

    // Iniciar matriz del mapa
    int grid[ROW][COL]{};
    // Color de los botones
    sf::Color celdaColor[ROW][COL];
    // Seleccion de torres
    int modoSeleccionado;  // 0 = ninguno, 1 = azul, 2 = rojo
    // Coordenadas de celda inicio
    Pair src;
    // Celda de fin
    Pair dest;
    // Posicion del cursor
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int genaracionOleada; // Generación de oleada

    // Temporizador para oleadas
    sf::Clock reloj;
    std::vector<VisualEnemy> enemigos; // enemigos en movimiento

    Wave wave; // Oleada de enemigos

};



#endif //CONTROLER_H
