#ifndef VIEW_H
#define VIEW_H
#include "Const.h"
#include <SFML/Graphics.hpp>

class View {
public:
    // Constructor
    explicit View(sf::RenderWindow& window);
    // Dibujar Mapa
    void mapa(const int grid[ROW][COL], const sf::Color celdaColor[ROW][COL]);
    // Dibujar botones para seleccionar tipo de torre
    void torres(int modoSeleccionado);
    // Efecto de resaltado con el cursor
    void drawHover(int posX, int posY);
    // Detecta click con el mouse
    int botonClick(int mouseX, int mouseY);
    // Dibuja los botones en la ventana
    void Boton();

private:
    sf::RenderWindow& window; // Referencia a la ventana renderizado

    // Textura y Sprite asociada para imagenes del mapa
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture texture1;
    sf::Sprite sprite1;

    // Botones para las torres
    sf::RectangleShape boton1;
    sf::RectangleShape boton2;
    sf::RectangleShape boton3;
    sf::RectangleShape botonOleada;

    // Dibuja celdas y colores
    void Celda(const int gric[ROW][COL]);
    void Color(const sf::Color celda_color[ROW][COL]);
};



#endif //VIEW_H
