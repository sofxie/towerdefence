#include "View.h"
#include "Const.h"
#include "VisualEnemy.h"
#include <sstream>
#include <string>


// Constructor
View::View(sf::RenderWindow &window)
: window(window){ // Botones

    // Fuente para texto de Oro
    text.setFont(font);
    text.setString("0");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(SIZE*13, SIZE);

    // Imagen del mapa
    texture.loadFromFile("Imagenes/pasto.png");
    texture1.loadFromFile("Imagenes/pasto2.png");
    texturebg.loadFromFile("Imagenes/Panel.png");

    texCorazon.loadFromFile("Imagenes/Vida.png");
    textureGO.loadFromFile("Imagenes/GameOver.png");


    // Imagen de los botones
    textureBot1.loadFromFile("Imagenes/TArqueroBot.jpeg");
    textureBot2.loadFromFile("Imagenes/TArtilleroBot.jpeg");
    textureBot3.loadFromFile("Imagenes/TMagoBot.jpeg");
    textureBotOleada.loadFromFile("Imagenes/VillanoBOT.png");

    // Asociar textura a sprite
    sprite.setTexture(texture);
    sprite1.setTexture(texture1);
    spritebg.setTexture(texturebg);
    spriteBot1.setTexture(textureBot1);
    spriteBot2.setTexture(textureBot2);
    spriteBot3.setTexture(textureBot3);
    spriteBotOleada.setTexture(textureBotOleada);

    // Modificar tamano de imagen
    sprite.setScale(static_cast<float>(SIZE) / texture.getSize().x,
    static_cast<float>(SIZE) / texture.getSize().y);
    sprite1.setScale(static_cast<float>(SIZE) / texture1.getSize().x,
    static_cast<float>(SIZE) / texture1.getSize().y);
    spritebg.setScale(static_cast<float>(400) / texture1.getSize().x,
    static_cast<float>(465) / texture1.getSize().y);
    spriteBot1.setScale(0.05f, 0.05f);
    spriteBot2.setScale(0.05f, 0.05f);
    spriteBot3.setScale(0.05f, 0.05f);
    spriteBotOleada.setScale(static_cast<float>(382) / texture1.getSize().x,
    static_cast<float>(300) / texture1.getSize().y);

    // Posicionar y diseñar botones
    spritebg.setPosition(SIZE*10, 0);
    spriteBot1.setPosition(SIZE * 11.2, SIZE*4.5);
    spriteBot2.setPosition(SIZE * 12.75, SIZE*4.5);
    spriteBot3.setPosition(SIZE * 14.3, SIZE*4.5);
    spriteBotOleada.setPosition(SIZE * 11.2, SIZE * 3);

    auto initText = [&](sf::Text& txt, float yOffset) {
        txt.setFont(font);
        txt.setCharacterSize(14);
        txt.setFillColor(sf::Color::White);
        txt.setPosition(SIZE * 11.2f, yOffset);
    };

    initText(txtEnemigosEliminados, SIZE * 6.4f);
    initText(txtOleada, SIZE * 6.7f);
    initText(txtFitness, SIZE * 7.9f);
    initText(txtMutacionesProba, SIZE * 7.3f);
    initText(txtMutacionesOcurridas, SIZE * 7.6f);
    initText(txtNivelTorre, SIZE * 7.0f);


}

// Dibujar las celdas del mapa
void View::mapa(const int grid[ROW][COL], sf::Sprite celdaColor[ROW][COL]) {
    Celda(grid);
    Color(celdaColor);
}

// Agregar Botones a la ventana
void View::torres(int modoSeleccionado) {
    Boton(); // Agrega boton
    LoadFont(font,"Font/Pixel Emulator.otf"); // Agregar texto
}

// Texto
void View::LoadFont(sf::Font &font, std::string str) {
    if (!font.loadFromFile(str)) {
        std::cerr << "Error loading font" << std::endl;
    }
}

// Obtiene valor de Oro
void View::Oro(int Oro) {
    std::stringstream ss;
    ss<<Oro;
    text.setString(ss.str());
}

// Funcion para dibujar los corazones
void View::drawVida(int vidas) {
    const int maxVidas = 3;
    const int startX = SIZE * 12;
    const int y = SIZE * 2;
    for (int i = 0; i < vidas && i < maxVidas; ++i) {
        sf::Sprite spriteVida;
        spriteVida.setTexture(texCorazon);
        spriteVida.setScale(static_cast<float>(200) / texture1.getSize().x,
        static_cast<float>(200) / texture1.getSize().y);
        spriteVida.setPosition(startX + SIZE * i, y);
        window.draw(spriteVida);
    }
}

// Funcion Proyecta el GameOver
void View::GameOver() {
    spriteGO.setTexture(textureGO);
    spriteGO.setScale(static_cast<float>(1000) / textureGO.getSize().x,
    static_cast<float>(600) / textureGO.getSize().y);
    spriteGO.setPosition(0,0);
    window.draw(spriteGO);

}
void View::updateStats(int enemigosEliminados, int oleadaActual, int nivelTorre,
                       const std::vector<std::string>& enemyDescriptions,
                       float probabilidadMutacion, int mutacionesOcurridas) {
    txtEnemigosEliminados.setString("Enemigos eliminados: " + std::to_string(enemigosEliminados));
    txtOleada.setString("Numero de Oleada: " + std::to_string(oleadaActual));
    txtMutacionesProba.setString("Probabilidad de mutacion: " + std::to_string(static_cast<int>(probabilidadMutacion)) + "%");
    txtMutacionesOcurridas.setString("Mutaciones ocurridas: " + std::to_string(mutacionesOcurridas));
    txtNivelTorre.setString("Nivel de Torre: " + std::to_string(nivelTorre));

    // Mostrar hasta 5 enemigos en pantalla
    std::string resumenEnemigos = "Enemigos actuales:\n";
    int count = 0;
    for (const auto& desc : enemyDescriptions) {
        resumenEnemigos += "- " + desc + "\n";
        if (++count >= 5) break;  // Limitar a 5 líneas
    }

    txtFitness.setString(resumenEnemigos);
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
    if (spriteBotOleada.getGlobalBounds().contains(mouseX, mouseY)) return 4;
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
    // Dibujar elementos de la UI
    window.draw(spritebg);
    window.draw(spriteBot1);
    window.draw(spriteBot2);
    window.draw(spriteBot3);
    window.draw(spriteBotOleada);
    window.draw(text);
    window.draw(txtEnemigosEliminados);
    window.draw(txtOleada);
    window.draw(txtFitness);
    window.draw(txtMutacionesProba);
    window.draw(txtMutacionesOcurridas);
    window.draw(txtNivelTorre);
}







