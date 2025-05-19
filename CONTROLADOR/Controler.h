#ifndef CONTROLER_H
#define CONTROLER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "View.h"
#include "Enemigos/Wave.h"
#include "Enemigos/EnemyController.h"
#include "VisualEnemy.h"
#include "Torre/Torre.h"
#include <vector>


class Controler {
public:
    Controler(std::vector<std::shared_ptr<EnemyController>>& listaDeEnemigos); // Constructor
    void run(); // Bucle del juego
    using Pair = std::pair<int, int>; // Par de coordenadas
    void events(); // Funcion que maneja controles del juego
    void update(); // Actualizar mapa
    void render(); // Proyectar en la interfaz
    void crearOleada(std::vector<Pair> ruta); // Crear oleada de enemigos


private:
    sf::RenderWindow window;
    Map mapa; // Incluir clases
    View vista;
    std::vector<std::shared_ptr<Torre>> torres; // Lista de Torres
    std::vector<std::shared_ptr<EnemyController>>& listaDeEnemigos; // Lista de Enemigos
    // Iniciar matriz del mapa
    int grid[ROW][COL]{};
    // Imagenes de Torres
    sf::Sprite celdaColor[ROW][COL];
    sf::Texture TArquero1;
    sf::Texture TArtillero1;
    sf::Texture TMago1;
    sf::Texture TArquero2;
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
    std::vector<VisualEnemy> enemigos;
    Wave wave; // Oleada de enemigos
};



#endif //CONTROLER_H
