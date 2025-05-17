#ifndef WAVE_H
#define WAVE_H

#include "Enemy.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <random>
#include <iostream>

class Wave {
private:
    // Atributos de la clase
    std::vector<std::unique_ptr<Enemy>> enemies;
    int generation;
    int timesGetEnemiesCalled = 0; // Contador de llamadas a getEnemies()

    // Funciones de ayuda para evolución
    float mutateFloat(float value, float minDelta, float maxDelta) const;
    int mutateInt(int value, int minDelta, int maxDelta) const;
    std::unique_ptr<Enemy> evolveFromBest(const Enemy& best) const;
    const Enemy* findBest(const std::vector<std::unique_ptr<Enemy>>& group) const;
    void evolveGroup(std::vector<std::unique_ptr<Enemy>>& group, EnemyType type);

public:
    Wave(int gen = 1);

    void spawnEnemies(); // Genera enemigos aleatorios
    void evolve(); // Evoluciona la oleada de enemigos(Funcion a mejorar)
    void printEnemiesInfo() const; // Imprime información de los enemigos generados

    std::vector<std::unique_ptr<Enemy>>& getEnemies();
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const; // Devuelve la lista de enemigos
    int getGeneration() const; // Devuelve la generación de la oleada

};

#endif // WAVE_H
