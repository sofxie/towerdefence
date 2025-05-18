#ifndef WAVE_H
#define WAVE_H

#include "Enemy.h"
#include <vector>
#include <memory>

class Wave {
private:
    // Atributos de la clase
    std::vector<std::unique_ptr<Enemy>> enemies;
    int generation;

public:
    Wave(int gen = 1);

    void spawnEnemies(); // Genera enemigos aleatorios
    void evolve(); // Evoluciona la oleada de enemigos(Funcion a mejorar)

    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const; // Devuelve la lista de enemigos
    int getGeneration() const; // Devuelve la generación de la oleada
};

#endif // WAVE_H
