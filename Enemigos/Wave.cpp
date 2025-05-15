#include "Wave.h"
#include <random>

Wave::Wave(int gen) : generation(gen) {
    spawnEnemies();
}

void Wave::spawnEnemies() {
    enemies.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3); // 0 a 3 para 4 tipos de enemigos
    for (int i = 0; i < 10; ++i) {
        switch (dist(gen)) {
            case 0: enemies.push_back(std::make_unique<Ogre>()); break; // Ogros
            case 1: enemies.push_back(std::make_unique<DarkElf>()); break; // Elfos oscuros
            case 2: enemies.push_back(std::make_unique<Harpy>()); break; // Hárpias
            case 3: enemies.push_back(std::make_unique<Mercenary>()); break; // Mercenarios
        }
    }
}

void Wave::evolve() {
    generation++;
    for (auto& e : enemies) {
        int newHealth = static_cast<int>(e->getHealth() * 150.5f);
    }
}

const std::vector<std::unique_ptr<Enemy>>& Wave::getEnemies() const {
    return enemies;
}

int Wave::getGeneration() const {
    return generation;
}

