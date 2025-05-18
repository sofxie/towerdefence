#include "View.h"
#include "Const.h"
#include "VisualEnemy.h"

// Constructor
View::View(sf::RenderWindow &window)
    : window(window), // Referencia a la ventana que dibuja
    boton1(sf::Vector2f(SIZE * 2, SIZE)), // Botones
    boton2(sf::Vector2f(SIZE * 2, SIZE)),
    boton3(sf::Vector2f(SIZE * 2, SIZE)),
    botonOleada(sf::Vector2f(SIZE*2, SIZE)){

    // Imagen del mapa
    texture.loadFromFile("Imagenes/pasto.png");
    texture1.loadFromFile("Imagenes/pasto2.png");

    // Asociar textura a sprite
    sprite.setTexture(texture);
    sprite1.setTexture(texture1);

    // Modificar tamano de imagen
    sprite.setScale(static_cast<float>(SIZE) / texture.getSize().x,
    static_cast<float>(SIZE) / texture.getSize().y);
    sprite1.setScale(static_cast<float>(SIZE) / texture1.getSize().x,
    static_cast<float>(SIZE) / texture1.getSize().y);

    // Posicionar y diseñar botones
    boton1.setPosition(SIZE * 11, SIZE);
    boton1.setFillColor(sf::Color::Blue);

    boton2.setPosition(SIZE * 11, SIZE * 3);
    boton2.setFillColor(sf::Color::Red);

    boton3.setPosition(SIZE * 11, SIZE * 5);
    boton3.setFillColor(sf::Color::Yellow);

    botonOleada.setPosition(SIZE * 11, SIZE * 7);
    botonOleada.setFillColor(sf::Color::Magenta);
}

// Dibujar las celdas del mapa
void View::mapa(const int grid[ROW][COL], const sf::Color celdaColor[ROW][COL]) {
    Celda(grid);
    Color(celdaColor);
}

// Agregar Botones a la ventana
void View::torres(int modoSeleccionado) {
    Boton(); // Agrega boton
}

// Efecto resaltado con el cursor
void View::drawHover(int mouseX, int mouseY) {
    int col = mouseX / SIZE;
    int row = mouseY / SIZE;

    if (row >= 0 && row < ROW && col >= 0 && col < COL) {
        sf::RectangleShape highlight(sf::Vector2f(SIZE, SIZE));
        highlight.setPosition(col * SIZE, row * SIZE);
        highlight.setFillColor(sf::Color(0, 255, 255, 100)); // Amarillo transparente
        window.draw(highlight);
    }
}

// Identificar Clicks en un boton
int View::botonClick(int mouseX, int mouseY) {
    if (boton1.getGlobalBounds().contains(mouseX, mouseY)) return 1;
    if (boton2.getGlobalBounds().contains(mouseX, mouseY)) return 2;
    if (boton3.getGlobalBounds().contains(mouseX, mouseY)) return 3;
    if (botonOleada.getGlobalBounds().contains(mouseX, mouseY)) return 4;
    return 0;
}

// Dibujar las celdas del mapa intercaladas
void View::Celda(const int grid[ROW][COL]) {
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
}

// Pintar las celdas de color
void View::Color(const sf::Color celdaColor[ROW][COL]) {
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
}

// Dibuja los botones en la interfaz
void View::Boton() {
    window.draw(boton1);
    window.draw(boton2);
    window.draw(boton3);
    window.draw(botonOleada);
}

