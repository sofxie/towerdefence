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
#include "Const.h"
#include "Enemigos/Enemy.h"
#include "iostream"
#include "Torre/Torre_Arco.h"

#include <memory>


class Controler {
public:
    Controler(std::vector<std::shared_ptr<EnemyController>>& listaDeEnemigos); // Constructor
    void run(); // Bucle del juego
    using Pair = std::pair<int, int>; // Par de coordenadas
    void events(); // Funcion que maneja controles del juego
    void update(); // Actualizar mapa
    void render(); // Proyectar en la interfaz
    void crearOleada(std::vector<Pair> ruta); // Crear oleada de enemigos
    bool oleadasActivas = false; // Comprobar si hay oleadas activas
    bool activados = false;
    void eliminarenemigos(); // Elimina Enemigos de la lista
    std::vector<std::pair<int, int>> getPosicionEnemigos() const;
    int Oro = 500;
    int Vida = 3;
    int kills = 0;



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
    sf::Texture TArtillero2;
    sf::Texture TMago2;
    sf::Texture TArquero3;
    sf::Texture TArtillero3;
    sf::Texture TMago3;

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
    sf ::Clock oleadaClock;// Temporizador de oleadas
    std::vector<std::unique_ptr<Enemy>> enemiesToSpawn;  // Enemigos por salir
    std::vector<Pair> rutaOleada;                        // Ruta para los enemigos
    int spawnIndex = 0;                                  // Índice del siguiente enemigo
    sf::Clock spawnClock;                                // Controla el tiempo entre spawns}
    sf::Clock rutaUpdateClock; // Temporizador para recalcular rutas

    int probabilidad = 0;
    int Oledas = 0; // Contador de oleadas
    int mutacionesOcurridas = 0; // Contador de mutaciones
    int PrimerO = 0; // Primer oleada
};



#endif //CONTROLER_H
