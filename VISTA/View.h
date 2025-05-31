#ifndef VIEW_H
#define VIEW_H
#include "Const.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <deque>
#include "Torre/Torre.h"

class View {
public:
    // Constructor
    explicit View(sf::RenderWindow& window);
    // Dibujar Mapa
    void mapa(const int grid[ROW][COL], sf::Sprite celdaColor[ROW][COL]);
    // Dibujar botones para seleccionar tipo de torre
    void torres(int modoSeleccionado);
    // Efecto de resaltado con el cursor
    void drawHover(int posX, int posY, int grid[10][10], std::vector<std::shared_ptr<Torre>> listTorres);
    // Detecta click con el mouse
    int botonClick(int mouseX, int mouseY);
    // Dibuja los botones en la ventana
    void Boton();
    // Obtener el valor del oro
    void Oro(int Oro);
    // Dibuja la cantidad de Vida
    void drawVida(int Vida);
    // Proyectar el GameOver
    void GameOver(int kills);
    //Metodos para el scroll
    void addLogMessage(const std::string& message, const sf::Color& color = sf::Color::White);
    void drawLog();
    void handleLogEvent(const sf::Event& event);
    void updateStats(int enemigosEliminados, int oleadaActual, int nivelTorre,
                           const std::vector<std::string>& enemyDescriptions,
                           int probabilidadMutacion, int mutacionesOcurridas);
    float getFitnessScrollOffset() const { return fitnessScrollOffset; }
    void setFitnessScrollOffset(float offset) { fitnessScrollOffset = offset; }




private:
    sf::RenderWindow& window; // Referencia a la ventana renderizado

    // Para texto del juego
    sf::Font font;
    sf::Text text;

    // Textura y Sprite asociada para imagenes del mapa
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture texture1;
    sf::Sprite sprite1;
    sf::Texture texturebg;
    sf::Sprite spritebg;
    sf::Texture texCorazon;
    sf::Texture textureGO;
    sf::Sprite spriteGO;
    sf::Texture textureCas;
    sf::Sprite spriteCas;

    // Botones para las torres
    sf::Texture textureBot1;
    sf::Sprite spriteBot1;
    sf::Texture textureBot2;
    sf::Sprite spriteBot2;
    sf::Texture textureBot3;
    sf::Sprite spriteBot3;
    sf::Texture textureBotOleada;
    sf::Sprite spriteBotOleada;

    // Cargar la fuente
    void LoadFont(sf::Font& font,std::string str);

    // Dibuja celdas y colores
    void Celda(const int gric[ROW][COL]);
    void Color( sf::Sprite celdaColor[ROW][COL]);
    //Estadisticas
    sf::Text txtEnemigosEliminados;
    sf::Text txtOleada;
    sf::Text txtFitness;
    sf::Text txtMutacionesProba;
    sf::Text txtMutacionesOcurridas;
    sf:: Text txtNivelTorre;
    sf:: Text txtKillsFinales;

    float fitnessScrollOffset = 0.f;
    sf::View fitnessView;
    sf::Text fitnessCopy;
    sf::FloatRect fitnessViewportRect;

};


#endif //VIEW_H
