#include <SFML/Graphics.hpp>
#include "Map.h"
#include <utility>
using Pair = std::pair<int, int>;
using namespace std;
// Tamaño de celda
const int SIZE = 40;

int main() {
    // Crear una ventana de 800x600
    sf::RenderWindow window(sf::VideoMode(COL * SIZE, ROW * SIZE), "Tower Defense");

    // Iniciar mapa
    int grid[ROW][COL] = { 0 };

    // Rellenarlo con 1
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            grid[i][j] = 1; //
    Map mapa;
    // Celda de inicio
    Pair src = make_pair(8, 0);
    // Celda de fin
    Pair dest = make_pair(0, 0);
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
                sf::RectangleShape cell(sf::Vector2f(SIZE - 1, SIZE - 1));
                cell.setPosition(j * SIZE, i * SIZE);

                if (grid[i][j] == 0)
                    cell.setFillColor(sf::Color::Black);         // Ruta encontrada
                else
                    cell.setFillColor(sf::Color(220, 220, 220)); // Libre

                window.draw(cell);
            }
        }

        window.display();               // Mostrar la ventana
    }

    return 0;
}