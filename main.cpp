#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <utility>
using Pair = std::pair<int, int>;
using namespace std;
// Tamaño de celda
const int SIZE = 40;

int main() {
    // Crear una ventana de 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");

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

    // Rellenarlo con 1
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            grid[i][j] = 1; //
    Map mapa;
    // Celda de inicio
    Pair src = make_pair(14, 0);
    // Celda de fin
    Pair dest = make_pair(0, 14);
    // Usar clases mapa

    mapa.aEstrellita(grid,src, dest);
    // Bucle principal del juego
    while (window.isOpen()) { // es como mainloop en tkinter
        sf::Event event;
        while (window.pollEvent(event)) {
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
        window.display();               // Mostrar la ventana
    }

    return 0;
}