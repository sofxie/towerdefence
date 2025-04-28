#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana de 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");

    // Bucle principal del juego
    while (window.isOpen()) { // es como mainloop en tkinter
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Limpiar la ventana con color negro
        window.display();               // Mostrar la ventana
    }

    return 0;
}