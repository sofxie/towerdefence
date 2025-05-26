#ifndef VISUALENEMY_H
#define VISUALENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemigos/Enemy.h"
#include "Const.h"
#include <cmath>
#include "Map.h"

using Pair = std::pair<int, int>;

struct VisualEnemy {
    // Puntero para referenciar cada enemigo
    std::shared_ptr<Enemy> enemy;
    // Ruta a seguir
    std::vector<Pair> path;
    // Cartidad de espacio recorrido
    int currentStep = 0;
    // Posicion actual de enemigo
    sf::Vector2f position;
    sf::Vector2f targetPosition;

    // Imagen de los enemigos
    sf::Texture textureEnemy;
    sf::Sprite spriteEnemy;

    // Animacion de los enemigos
    float timer = 0.0f;
    // Duracion de cada frame
    float frameDuration = 0.5f;
    int currentFrame = 0;
    int totalFrames = 1;
    // Tamaño
    int frameWidth = 0;
    int frameHeight = 0;
    struct TextureManager {
        static sf::Texture& get(EnemyType type) {
            static sf::Texture ogre, harpy, mercenary, elf;
            static bool loaded = false;
            if (!loaded) {
                ogre.loadFromFile("Imagenes/Ogro.png");
                harpy.loadFromFile("Imagenes/Harpy.png");
                mercenary.loadFromFile("Imagenes/Mercenary.png");
                elf.loadFromFile("Imagenes/Elf.png");
                loaded = true;
            }

            switch (type) {
                case EnemyType::Ogre: return ogre;
                case EnemyType::Harpy: return harpy;
                case EnemyType::Mercenary: return mercenary;
                case EnemyType::DarkElf: return elf;
            }
            return ogre; // fallback
        }
    };
    bool vivo = true;

    VisualEnemy(std::shared_ptr<Enemy> e, const std::vector<Pair>& p)
        : enemy(e), path(p) {

        // Imagen según tipo de enemigo
        EnemyType tipo = enemy->getType();
        std::string file;

        // Cargar Imagen dependiendo del tipo
        if (tipo == EnemyType::Ogre) {
            file = "Imagenes/Ogro.png";
            totalFrames = 5;
            frameWidth = 204;
            frameHeight = 358;
        } else if (tipo == EnemyType::Harpy) {
            file = "Imagenes/Harpy.png";
            totalFrames = 5;
            frameWidth = 200;
            frameHeight = 352;
        } else if (tipo == EnemyType::Mercenary) {
            file = "Imagenes/Mercenary.png";
            totalFrames = 5;
            frameWidth = 290;
            frameHeight = 491;
        } else if (tipo == EnemyType::DarkElf) {
           file = "Imagenes/Elf.png";
            totalFrames = 4;
            frameWidth = 333;
            frameHeight = 661;
        }

        if (!textureEnemy.loadFromFile(file)) {
            std::cerr << "Error cargando imagen: " << file << "\n";
        }
        // Asociar textura con sprite
        spriteEnemy.setTexture(TextureManager::get(tipo));
        spriteEnemy.setTextureRect({0, 0, frameWidth, frameHeight});
        spriteEnemy.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
        int maxDimension = std::max(frameWidth, frameHeight);
        if (maxDimension <= 0) maxDimension = 1;

        float scale = SIZE / static_cast<float>(maxDimension);
        spriteEnemy.setScale(scale, scale);

        if (!path.empty()) {
            position = sf::Vector2f(path[0].second * SIZE, path[0].first * SIZE);
            if (path.size() > 1) {
                targetPosition = sf::Vector2f(path[1].second * SIZE, path[1].first * SIZE);
            }
        }
    }
    void Speed(float vel) {
        enemy->setSpeed(vel);
        vivo = false;
    }
    void actualizar(float deltaTime, int grid[ROW][COL], Map& mapa) {
        // Animar a los enemigos
        timer += deltaTime;
        if (timer >= frameDuration) {
            timer = 0.0f;
            currentFrame++;
            if (currentFrame >= totalFrames) {
                currentFrame = 0;
            }
            int textureWidth = textureEnemy.getSize().x;

            if ((currentFrame + 1) * frameWidth <= textureWidth) {
                spriteEnemy.setTextureRect({ currentFrame * frameWidth, 0, frameWidth, frameHeight });
            } else {
                std::cerr << "Frame fuera del límite de textura (" << currentFrame << "). Reiniciando.\n";
                currentFrame = 0;
                spriteEnemy.setTextureRect({ 0, 0, frameWidth, frameHeight });
            }
        }
        // Movimiento u otras lógicas
        spriteEnemy.setPosition(position.x + SIZE / 2, position.y + SIZE / 2);
        if (currentStep >= path.size() - 1) return;

        // Verificar si la siguiente celda está bloqueada
        if (currentStep + 1 < path.size()) {
            Pair nextCell = path[currentStep + 1];
            if (grid[nextCell.first][nextCell.second] != 1) {
                // Recalcular ruta desde la posición actual
                Pair currentCell = getGridPosition();
                Pair destCell = path.back();  // Destino original

                std::vector<Pair> newPath = mapa.getPath(grid, currentCell, destCell);

                if (!newPath.empty()) {
                    setPath(newPath);  // Actualizar la ruta
                } else {
                    vivo = false;  // No hay camino válido
                    return;
                }
            }
        }

        // Movimiento original (sin cambios)
        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) direction /= length;

        float speed = enemy->getSpeed();
        position += direction * speed * deltaTime;

        if (std::abs(position.x - targetPosition.x) < 1.0f &&
            std::abs(position.y - targetPosition.y) < 1.0f) {
            currentStep++;
            if (currentStep < path.size() - 1) {
                targetPosition = sf::Vector2f(path[currentStep + 1].second * SIZE,
                                              path[currentStep + 1].first * SIZE);
            }
            }
    }

    void dibujar(sf::RenderWindow& window) {
        if (vivo) {
            window.draw(spriteEnemy);
        }
    }

    bool haTerminado() const {
        return currentStep >= path.size() - 1;
    }
    sf::Vector2f getPositionE() const {
        return position;
    }

    void setPath(const std::vector<Pair>& nuevaRuta) {
        if (!nuevaRuta.empty()) {
            path = nuevaRuta;
            currentStep = 0;
            position = sf::Vector2f(path[0].second * SIZE, path[0].first * SIZE);
            if (path.size() > 1) {
                targetPosition = sf::Vector2f(path[1].second * SIZE, path[1].first * SIZE);
            }
        }
    }


    std::pair<int, int> getGridPosition() const {
        int fila = static_cast<int>(position.y / SIZE);
        int columna = static_cast<int>(position.x / SIZE);
        return { fila, columna };
    }



};

#endif // VISUALENEMY_H
