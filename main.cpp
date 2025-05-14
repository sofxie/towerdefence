#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <utility>
#include <vector>
#include <ctime>



using Pair = std::pair<int, int>;
using namespace std;
// Tamaño de celda
const int SIZE = 60;
sf::Color celdaColor[ROW][COL];

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
    Pair src = make_pair(14, 0);
    // Celda de fin
    Pair dest = make_pair(0, 14);
    // Usar clases mapa

    mapa.aEstrellita(grid,src, dest);
    // Bucle principal del juego
    while (window.isOpen()) { // es como mainloop en tkinter
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
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int col = event.mouseButton.x / SIZE;
                    int row = event.mouseButton.y / SIZE;
                    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
                        std::cout << "Haz hecho clic en la celda: (" << row << ", " << col << ")\n";
                    }
                    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
                        if (modoSeleccionado == 1)
                            celdaColor[row][col] = sf::Color::Blue;
                        else if (modoSeleccionado == 2)
                            celdaColor[row][col] = sf::Color::Red;
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

        // Dibujar botón
        window.draw(boton1);
        window.draw(boton2);
        window.display();               // Mostrar la ventana
    }

    return 0;
}