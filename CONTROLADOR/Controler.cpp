#include "iostream"
#include "Controler.h"
#include "VisualEnemy.h"
#include "Enemigos/Wave.h"
#include "Map.h"
#include "Const.h"
#include "Torre/Torre.h"
#include "Enemigos/Enemy.h"
#include "Torre/Torre_Arco.h"
#include <vector>
#include <memory>

    using namespace std;


    // Constructor
Controler::Controler(std::vector<std::shared_ptr<EnemyController>>& enemigos)
        :
        // Crear una ventana de 800x600
        window(sf::VideoMode(800, 600), "Tower Defense"), // Inicializar
        modoSeleccionado(0), // Inicializar modo de torres (0 por default)
        listaDeEnemigos(enemigos),
        src({9,0}), // Coordenadas de Inicio
        dest({0,9}), // Coordenadas del Destino
        vista(window), // Inicializar clase vista
        genaracionOleada(0) // Inicializar generación de oleada

    {
        // Inicializar grid para el mapa
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j) {
                grid[i][j] = 1;  // Rellenarlo con 1 Accesible
            }
        reloj.restart();
    }

    // Ejecutar el juego
    void Controler::run() {
        while (window.isOpen()) {
            events(); // Llamar eventos para manejar interacciones
            update(); // Llamar actualizar para el estado de juego
            render(); // Llamar renderizado para dibujar el estado en la ventana
        }
    }

    // Crear oleada de enemigos
void Controler::crearOleada(std::vector<Pair> ruta) {
    static int llamadasOleadas = 0;

    // Activar control de oleadas
    if (!oleadasActivas) {
        oleadasActivas = true;
        std::cout << "Oleada activa\n";
    } else {
        std::cout << "Oleada no activa\n";
    }

    // Guardar ruta
    rutaOleada = ruta;

    // Nueva wave si es necesario
    if (wave.getGeneration() != genaracionOleada) {
        llamadasOleadas++;
        wave = Wave(genaracionOleada);
    }

    if (llamadasOleadas > 2) {
        wave.evolve();
    }

    // Preparar enemigos a spawnear
    const auto& currentEnemies = wave.getEnemies();
    enemiesToSpawn.clear();
    for (const auto& e : currentEnemies) {
        enemiesToSpawn.push_back(std::make_unique<Enemy>(*e));
    }

    // Reiniciar control de spawn
    spawnIndex = 0;
    spawnClock.restart();
    oleadaClock.restart();

    genaracionOleada++;
}


    // Comprobar si hay oleadas activas



    // Manejar eventos
    void Controler::events() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Click izquierdo
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Obtiene posiciones X y Y
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Verificar si fue presionado
                int boton = vista.botonClick(mouseX,mouseY);
                if (boton != 0) {
                    modoSeleccionado = boton;
                    std::cout << "Haz seleccionado el color: (" << modoSeleccionado <<std::endl;
                }
            // Calcular coordenada de celda presionado
            int col = event.mouseButton.x / SIZE;
            int row = event.mouseButton.y / SIZE;

            if (row >= 0 && row < ROW && col >= 0 && col < COL) {
                std::cout << "Haz hecho clic en la celda: (" << row << ", " << col << ")\n";
            }
            // Colocar tipo de torre, dependiendo del modoSeleccionado
            if (row >= 0 && row < ROW && col >= 0 && col < COL) {
                if (modoSeleccionado == 1){
                    if (mapa.blocked(grid, row, col)) {
                        grid[row][col] = 0;
                        TArquero1.loadFromFile("Imagenes/Arquero1.jpeg");
                        auto torre = std::make_shared<Torre_Arco>();
                        torre->setPosicion(row, col);
                        torres.push_back(torre);
                        celdaColor[row][col].setTexture(TArquero1);
                        celdaColor[row][col].setScale(0.051f, 0.051f);
                        bool found = mapa.aEstrellita(grid, src, dest);
                        if (!found) {
                            printf("ME BLOQUEARON\n");

                            // Revertir torre
                            grid[row][col] = 1;
                            celdaColor[row][col].setColor(sf::Color::Transparent);
                        }
                    }
            }
                else if (modoSeleccionado == 2) {
                    if (mapa.blocked(grid, row, col)) {
                        grid[row][col] = 0;
                        TArtillero1.loadFromFile("Imagenes/Artillero1.jpeg");
                        celdaColor[row][col].setTexture(TArtillero1);
                        celdaColor[row][col].setScale(0.051f, 0.051f);
                        bool found = mapa.aEstrellita(grid, src, dest);
                        if (!found) {
                            printf("ME BLOQUEARON\n");

                            // Revertir torre
                            grid[row][col] = 1;
                            celdaColor[row][col].setColor(sf::Color::Transparent);
                        }
                    }
                }
                else if (modoSeleccionado == 3) {
                    if (mapa.blocked(grid, row, col)) {
                        grid[row][col] = 0;
                        TMago1.loadFromFile("Imagenes/Mago1.jpeg");
                        celdaColor[row][col].setTexture(TMago1);
                        celdaColor[row][col].setScale(0.051f, 0.051f);
                        bool found = mapa.aEstrellita(grid, src, dest);
                        std::vector<Pair> ruta = mapa.getPath(grid, src, dest);
                        crearOleada(ruta);
                        if (!found) {
                            printf("ME BLOQUEARON\n");

                            // Revertir torre
                            grid[row][col] = 1;
                            celdaColor[row][col].setColor(sf::Color::Transparent);
                        }
                    }
                }
                else if (modoSeleccionado == 4) {
                    std::vector<Pair> ruta = mapa.getPath(grid, src, dest);
                    crearOleada(ruta);
                }
            }
        }
    }
    }

    void Controler::update() {
        float deltaTime = reloj.restart().asSeconds();

        if (oleadasActivas && oleadaClock.getElapsedTime().asSeconds() > 5.0f) {
            std::vector<Pair> ruta = mapa.getPath(grid, src, dest);
            crearOleada(ruta); // Nueva oleada automática
        }

        // Lanzar enemigos uno a uno
        if (spawnIndex < enemiesToSpawn.size() && spawnClock.getElapsedTime().asSeconds() >= 2.5f) {
            int startX = rutaOleada.front().first;
            int startY = rutaOleada.front().second;

            // Crea el enemigo visual y de lógica
            auto enemyCopy = std::make_shared<Enemy>(*enemiesToSpawn[spawnIndex]);
            listaDeEnemigos.emplace_back(std::make_shared<EnemyController>(enemyCopy, startX, startY));
            enemigos.emplace_back(enemyCopy, rutaOleada);

            spawnIndex++;
            spawnClock.restart();
        }

        // Actualizar enemigos existentes
        for (auto& enemigo : enemigos) {
            enemigo.actualizar(deltaTime);
        }

        // Actualizar torres
        for (auto& torre : torres) {
            torre->AtacarEnemigo(listaDeEnemigos);
        }
    }



    // Rederizar el mapa y los elementos graficos
    void Controler::render() {
        window.clear();
        vista.mapa(grid,celdaColor);
        vista.torres(modoSeleccionado);
        vista.drawHover(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        for (auto& enemigo : enemigos) {
            enemigo.dibujar(window);
        } // Dibujar enemigos
        window.display(); // Mostrar la ventana
    }
