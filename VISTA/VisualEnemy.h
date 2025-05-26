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
    std::shared_ptr<Enemy> enemy;
    std::vector<Pair> path;
    int currentStep = 0;
    sf::Vector2f position;
    sf::Vector2f targetPosition;
    sf::RectangleShape shape;
    bool vivo = true;
    bool ya_quite_vida = false;

    VisualEnemy(std::shared_ptr<Enemy> e, const std::vector<Pair>& p)
        : enemy(e), path(p) {

        shape.setSize(sf::Vector2f(SIZE * 0.8f, SIZE * 0.8f));
       // shape.setOrigin(shape.getSize() / 2.f); // Centrado para que no se vea desfasado

        // Color según tipo de enemigo
        EnemyType tipo = enemy->getType();

        if (tipo == EnemyType::Ogre) {
            shape.setFillColor(sf::Color::Green);
        } else if (tipo == EnemyType::Harpy) {
            shape.setFillColor(sf::Color::Red);
        } else if (tipo == EnemyType::Mercenary) {
            shape.setFillColor(sf::Color(0, 0, 139)); // Azul oscuro
        } else if (tipo == EnemyType::DarkElf) {
            shape.setFillColor(sf::Color::Black);
        } else {
            shape.setFillColor(sf::Color::White); // Color por defecto
        }


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
    void QuiteV() {
        ya_quite_vida = true;
    }
    void actualizar(float deltaTime, int grid[ROW][COL], Map& mapa) {
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
        if (vivo == false) {
        }
        else {
            shape.setPosition(position);
            window.draw(shape);
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
