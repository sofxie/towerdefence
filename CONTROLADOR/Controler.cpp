#include "iostream"
#include "Controler.h"
using namespace std;
#include "Const.h"

// Constructor
Controler::Controler()
    // Crear una ventana de 800x600
    : window(sf::VideoMode(800, 600), "Tower Defense"), // Inicializar
    modoSeleccionado(0), // Inicializar modo de torres (0 por default)
    src({9,0}), // Coordenadas de Inicio
    dest({0,9}), // Coordenadas del Destino
    vista(window)  // Inicializar clase vista
{
    // Inicializar grid para el mapa
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j) {
            celdaColor[i][j] = sf::Color::Transparent;
            grid[i][j] = 1;  // Rellenarlo con 1 Accesible
        }
}

// Ejecutar el juego
void Controler::run() {
    while (window.isOpen()) {
        events(); // Llamar eventos para manejar interacciones
        update(); // Llamar actualizar para el estado de juego
        render(); // Llamar renderizado para dibujar el estado en la ventana
    }
}

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

// Para actualizar estado del mapa
void Controler::update() {


}

// Rederizar el mapa y los elementos graficos
void Controler::render() {
    window.clear();
    vista.mapa(grid,celdaColor);
    vista.torres(modoSeleccionado);
    vista.drawHover(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    window.display(); // Mostrar la ventana
}
