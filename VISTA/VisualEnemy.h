#ifndef VISUALENEMY_H
#define VISUALENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemigos/Enemy.h"
#include "Const.h"
#include <cmath>

using Pair = std::pair<int, int>;

struct VisualEnemy {
    std::shared_ptr<Enemy> enemy;
    std::vector<Pair> path;
    int currentStep = 0;
    sf::Vector2f position;
    sf::Vector2f targetPosition;
    sf::RectangleShape shape;
    bool vivo = true;

    VisualEnemy(std::shared_ptr<Enemy> e, const std::vector<Pair>& p)
        : enemy(e), path(p) {
        shape.setSize(sf::Vector2f(SIZE * 0.8f, SIZE * 0.8f));
        shape.setFillColor(sf::Color::Black);

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
    void actualizar(float deltaTime) {
        if (currentStep >= path.size() - 1) return;

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
