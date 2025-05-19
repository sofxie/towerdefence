#include "View.h"
#include "Const.h"
#include "VisualEnemy.h"

// Constructor
View::View(sf::RenderWindow &window)
    : window(window), // Referencia a la ventana que dibuja
    botonOleada(sf::Vector2f(SIZE*2, SIZE)){ // Botones

    // Imagen del mapa
    texture.loadFromFile("Imagenes/pasto.png");
    texture1.loadFromFile("Imagenes/pasto2.png");

    // Imagen de los botones
    textureBot1.loadFromFile("Imagenes/TArquerosBot.png");
    textureBot2.loadFromFile("Imagenes/TArtilleroBot.jpeg");
    textureBot3.loadFromFile("Imagenes/TMagoBot.png");

    // Asociar textura a sprite
    sprite.setTexture(texture);
    sprite1.setTexture(texture1);
    spriteBot1.setTexture(textureBot1);
    spriteBot2.setTexture(textureBot2);
    spriteBot3.setTexture(textureBot3);

    // Modificar tamano de imagen
    sprite.setScale(static_cast<float>(SIZE) / texture.getSize().x,
    static_cast<float>(SIZE) / texture.getSize().y);
    sprite1.setScale(static_cast<float>(SIZE) / texture1.getSize().x,
    static_cast<float>(SIZE) / texture1.getSize().y);
    spriteBot1.setScale(0.06f, 0.06f);
    spriteBot2.setScale(0.06f, 0.06f);
    spriteBot3.setScale(0.06f, 0.06f);

    // Posicionar y diseñar botones
    spriteBot1.setPosition(SIZE * 11, SIZE);
    spriteBot2.setPosition(SIZE * 11, SIZE * 3);
    spriteBot3.setPosition(SIZE * 11, SIZE * 5);
    botonOleada.setPosition(SIZE * 11, SIZE * 7);
    botonOleada.setFillColor(sf::Color::Magenta);
}

// Dibujar las celdas del mapa
void View::mapa(const int grid[ROW][COL], sf::Sprite celdaColor[ROW][COL]) {
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
    if (spriteBot1.getGlobalBounds().contains(mouseX, mouseY)) return 1;
    if (spriteBot2.getGlobalBounds().contains(mouseX, mouseY)) return 2;
    if (spriteBot3.getGlobalBounds().contains(mouseX, mouseY)) return 3;
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
void View::Color( sf::Sprite celdaColor[ROW][COL]) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (celdaColor[i][j].getTexture() != nullptr) {
                celdaColor[i][j].setPosition(j * SIZE, i * SIZE);
                window.draw(celdaColor[i][j]);
            }
        }
    }
}

// Dibuja los botones en la interfaz
void View::Boton() {
    window.draw(spriteBot1);
    window.draw(spriteBot2);
    window.draw(spriteBot3);
    window.draw(botonOleada);
}

