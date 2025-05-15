#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <utility>
#include "Wave.h"
#include "Enemy.h"
#include <vector>
#include <ctime>
#include <cmath>

using Pair = std::pair<int, int>;

using namespace std;

// Tamaño de celda
const int SIZE = 60;
sf::Color celdaColor[ROW][COL];

struct VisualEnemy {
    std::shared_ptr<Enemy> enemy; // enemigo
    std::vector<Pair> path; // ruta
    int currentStep = 0; // paso actual
    sf::Vector2f position; // posición actual en pixeles
    sf::Vector2f targetPosition; // destino actual
    sf::RectangleShape shape; // forma del enemigo

    VisualEnemy(std::shared_ptr<Enemy> e, const std::vector<Pair>& p)
        : enemy(e), path(p) {
        shape.setSize(sf::Vector2f(SIZE * 0.8f, SIZE * 0.8f)); // un poco más pequeño para que se vea bien, se diferencie del camino
        shape.setFillColor(sf::Color::Black);

        if (!path.empty()) {
            currentStep = 0;
            position = sf::Vector2f(path[0].second * SIZE, path[0].first * SIZE);
            if (path.size() > 1)
                targetPosition = sf::Vector2f(path[1].second * SIZE, path[1].first * SIZE);
        }
    }

    void actualizar(float deltaTime) {
        if (currentStep >= path.size() - 1) return;

        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) direction /= length;

        float speed = enemy->getSpeed() * 60.0f; // Velocidad en píxeles por segundo
        position += direction * speed * deltaTime;

        // Si llegamos o pasamos el destino
        if (std::abs(position.x - targetPosition.x) < 1.0f && std::abs(position.y - targetPosition.y) < 1.0f) {
            currentStep++;
            if (currentStep < path.size() - 1) {
                targetPosition = sf::Vector2f(path[currentStep + 1].second * SIZE,
                                              path[currentStep + 1].first * SIZE);
            }
        }
    }

    void dibujar(sf::RenderWindow& window) {
        shape.setPosition(position);
        window.draw(shape);
    }

    bool haTerminado() const {
        return currentStep >= path.size() - 1;
    }
};


int main() {
    // Crear una ventana de 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");

    int modoSeleccionado = 0;  // 0 = ninguno, 1 = azul, 2 = rojo

    sf::RectangleShape boton1(sf::Vector2f(SIZE * 2, SIZE));
    boton1.setPosition(SIZE * 11, SIZE);
    boton1.setFillColor(sf::Color::Blue);

    sf::RectangleShape boton2(sf::Vector2f(SIZE * 2, SIZE));
    boton2.setPosition(SIZE * 11, SIZE * 3);
    boton2.setFillColor(sf::Color::Red);

    sf::RectangleShape boton3(sf::Vector2f(SIZE * 2, SIZE));
    boton3.setPosition(SIZE * 11, SIZE * 5);
    boton3.setFillColor(sf::Color::Yellow);

    //boton para invocar la oleada
    sf::RectangleShape botonOleada(sf::Vector2f(SIZE * 2, SIZE));
    botonOleada.setPosition(SIZE * 11, SIZE * 7);
    botonOleada.setFillColor(sf::Color(255, 140, 0)); // Naranja (Orange)


    // Imagen del mapa
    sf::Texture texture;
    sf::Texture texture1;
    texture.loadFromFile("Imagenes/pasto.png");
    texture1.loadFromFile("Imagenes/pasto2.png");

    sf::Sprite sprite(texture);
    sf::Sprite sprite1(texture1);

    sprite.setScale(static_cast<float>(SIZE) / texture.getSize().x,
    static_cast<float>(SIZE) / texture.getSize().y);
    sprite1.setScale(static_cast<float>(SIZE) / texture1.getSize().x,
    static_cast<float>(SIZE) / texture1.getSize().y);

    // Iniciar mapa
    int grid[ROW][COL] = { 0 };

    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            celdaColor[i][j] = sf::Color::Transparent;

    // Rellenarlo con 1
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            grid[i][j] = 1; //
    Map mapa;
    // Celda de inicio
    Pair src = make_pair(9, 0);
    // Celda de fin
    Pair dest = make_pair(0, 9);
    // Usar clases mapa

    mapa.aEstrellita(grid,src, dest);

    // Crear oleada de enemigos(Prueba)
    Wave oleada(2); // Primera oleada ;
    std::vector<VisualEnemy> enemigosVisuales;

    auto crearOleada = [&]() {
        enemigosVisuales.clear();
        oleada = Wave(oleada.getGeneration() + 1); // Generar nueva oleada
        for (const auto& enemigo : oleada.getEnemies()) { // Recorrer enemigos
            std::vector<Pair> path = mapa.getPath(grid, src, dest);
            enemigosVisuales.emplace_back(std::make_shared<Enemy>(*enemigo), path);
            std::cout << "oleada creada con exito\n";
        }
    };



    // Bucle principal del juego
    while (window.isOpen()) { // es como mainloop en tkinter

        sf::Clock clock;
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (boton1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    modoSeleccionado = 1;
                    std::cout << "Haz seleccionado el color: (" << modoSeleccionado << ")\n";
                }
                if (boton2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    modoSeleccionado = 2;
                    std::cout << "Haz seleccionado el color: (" << modoSeleccionado << ")\n";
                }
                if (boton3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    modoSeleccionado = 3;
                    std::cout << "Haz seleccionado el color: (" << modoSeleccionado << ")\n";
                }
                if (botonOleada.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    crearOleada();
                    std::cout << "Haz invocado una nueva oleada\n";
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int col = event.mouseButton.x / SIZE;
                    int row = event.mouseButton.y / SIZE;
                    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
                        std::cout << "Haz hecho clic en la celda: (" << row << ", " << col << ")\n";
                    }
                    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
                        if (modoSeleccionado == 1){
                            if (mapa.blocked(grid, row, col)) {
                                grid[row][col] = 0;
                                celdaColor[row][col] = sf::Color::Blue;
                                mapa.aEstrellita(grid,src, dest);
                            }
                    }
                        else if (modoSeleccionado == 2) {
                            if (mapa.blocked(grid, row, col)) {
                                grid[row][col] = 0;
                                celdaColor[row][col] = sf::Color::Red;
                                mapa.aEstrellita(grid,src, dest);
                            }
                        }
                        else if (modoSeleccionado == 3) {
                            if (mapa.blocked(grid, row, col)) {
                                grid[row][col] = 0;
                                celdaColor[row][col] = sf::Color::Yellow;
                                mapa.aEstrellita(grid,src, dest);
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear()  ; // Limpiar la ventana con color negro
        // Dibujar celdas
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                bool isDark = (i + j) % 2 == 0;
                if (isDark) {
                    sprite.setPosition(j * SIZE, i * SIZE);
                    window.draw(sprite); // Dibujar el mapa
                }else {
                    sprite1.setPosition(j * SIZE, i * SIZE);
                    window.draw(sprite1); // Dibujar el mapa
                }

            }
        }
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (celdaColor[i][j] != sf::Color::Transparent) {
                    sf::RectangleShape colorTile(sf::Vector2f(SIZE, SIZE));
                    colorTile.setPosition(j * SIZE, i * SIZE);
                    colorTile.setFillColor(celdaColor[i][j]);
                    window.draw(colorTile);
                }
            }
        }
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        int col = mouseX / SIZE;
        int row = mouseY / SIZE;

        if (row >= 0 && row < ROW && col >= 0 && col < COL) {
            sf::RectangleShape highlight(sf::Vector2f(SIZE, SIZE));
            highlight.setPosition(col * SIZE, row * SIZE);
            highlight.setFillColor(sf::Color(0, 255, 255, 100)); // Amarillo transparente
            window.draw(highlight);
        }
        // Actualizar enemigos
        // Actualizar enemigos
        for (auto& vEnemy : enemigosVisuales) {
            vEnemy.actualizar(deltaTime);
        }

        // Dibujar enemigos
        for (auto& vEnemy : enemigosVisuales) {
            vEnemy.dibujar(window);
        }


        // Dibujar botón
        window.draw(boton1);
        window.draw(boton2);
        window.draw(boton3);
        window.draw(botonOleada);
        window.display();               // Mostrar la ventana
    }

    return 0;
}