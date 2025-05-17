#include "Wave.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <map>

Wave::Wave(int gen) : generation(gen) {
    spawnEnemies();
}

void Wave::spawnEnemies() {
    enemies.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    for (int i = 0; i < 10; ++i) {
        switch (dist(gen)) {
            case 0: enemies.push_back(std::make_unique<Ogre>()); break;
            case 1: enemies.push_back(std::make_unique<DarkElf>()); break;
            case 2: enemies.push_back(std::make_unique<Harpy>()); break;
            case 3: enemies.push_back(std::make_unique<Mercenary>()); break;
        }
    }
}

float mutateFloat(float value, float minDelta, float maxDelta) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(minDelta, maxDelta);
    return value + dist(gen);
}

int mutateInt(int value, int minDelta, int maxDelta) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minDelta, maxDelta);
    return value + dist(gen);
}

std::unique_ptr<Enemy> evolveFromBest(const Enemy& best) {
    EnemyType type = best.getType();
    int health = mutateInt(best.getHealth(), 5, 20); // Aumento de vida
    float speed = mutateFloat(best.getSpeed(), 0.5f, 3.0f); // Aumento de velocidad
    int arRes = mutateInt(best.getArrowResistance(), 1, 5); // Aumento de resistencia a flechas
    int mgRes = mutateInt(best.getMagicResistance(), 1, 5); // Aumento de resistencia a magia
    int artRes = mutateInt(best.getArtilleryResistance(), 1, 5); // Aumento de resistencia a artillería

    switch (type) {
        case EnemyType::Ogre:
            return std::make_unique<Ogre>(health, speed, arRes, mgRes, artRes);
        case EnemyType::DarkElf:
            return std::make_unique<DarkElf>(health, speed, arRes, mgRes, artRes);
        case EnemyType::Harpy:
            return std::make_unique<Harpy>(health, speed, arRes, mgRes, artRes);
        case EnemyType::Mercenary:
            return std::make_unique<Mercenary>(health, speed, arRes, mgRes, artRes);
        default:
            return nullptr;
    }
}

const Enemy* findBest(const std::vector<std::unique_ptr<Enemy>>& group) {
    const Enemy* best = nullptr;
    float bestFitness = -1.0f;
    for (const auto& e : group) {
        float fitness = e->getHealth() + e->getSpeed();
        if (!best || fitness > bestFitness) {
            best = e.get();
            bestFitness = fitness;
        }
    }
    return best;
}

void Wave::evolve() { // Evoluciona la generación de enemigos
    generation++;

    // Agrupar enemigos por tipo
    std::map<EnemyType, std::vector<Enemy*>> porTipo;
    for (auto& e : enemies)
        porTipo[e->getType()].push_back(e.get());

    std::vector<std::unique_ptr<Enemy>> nuevaGeneracion;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> probMut(0.0f, 1.0f);

    for (auto& [tipo, grupo] : porTipo) {
        // Ordenar por fitness
        std::sort(grupo.begin(), grupo.end(), [](Enemy* a, Enemy* b) {
            auto fitness = [](Enemy* e) {
                return e->getHealth() * 1.0f + e->getSpeed() * 1.5f +
                       (e->getArrowResistance() + e->getMagicResistance() + e->getArtilleryResistance()) * 0.5f;
            };
            return fitness(a) > fitness(b);
        });

        Enemy* padre1 = grupo[0];
        Enemy* padre2 = grupo.size() > 1 ? grupo[1] : grupo[0];

        int baseCount = 2;
        if (generation % 2 == 0)
            baseCount += 1;

        for (int i = 0; i < baseCount; ++i) {
            int newHealth = (padre1->getHealth() + padre2->getHealth()) / 2;
            float newSpeed = (padre1->getSpeed() + padre2->getSpeed()) / 2.0f;
            int newArrowRes = (padre1->getArrowResistance() + padre2->getArrowResistance()) / 2;
            int newMagicRes = (padre1->getMagicResistance() + padre2->getMagicResistance()) / 2;
            int newArtilleryRes = (padre1->getArtilleryResistance() + padre2->getArtilleryResistance()) / 2;

            auto mutate = [&](auto val) {
                float chance = probMut(gen);
                float factor;
                if (chance < 0.2f) { // 20% de mutación favorable
                    std::uniform_real_distribution<float> dist(1.1f, 1.3f); // Mejora más notoria
                    factor = dist(gen);
                } else {
                    std::uniform_real_distribution<float> dist(0.9f, 1.1f); // Variación leve
                    factor = dist(gen);
                }
                return static_cast<decltype(val)>(val * factor);
            };

            newHealth = mutate(newHealth);
            newSpeed = mutate(newSpeed);
            newArrowRes = mutate(newArrowRes);
            newMagicRes = mutate(newMagicRes);
            newArtilleryRes = mutate(newArtilleryRes);

            std::unique_ptr<Enemy> nuevo;
            switch (tipo) {
                case EnemyType::Ogre: nuevo = std::make_unique<Ogre>(); break;
                case EnemyType::DarkElf: nuevo = std::make_unique<DarkElf>(); break;
                case EnemyType::Harpy: nuevo = std::make_unique<Harpy>(); break;
                case EnemyType::Mercenary: nuevo = std::make_unique<Mercenary>(); break;
            }

            if (nuevo) {
                nuevo->setStats(newHealth, newSpeed, newArrowRes, newMagicRes, newArtilleryRes);
                nuevaGeneracion.push_back(std::move(nuevo));
            }
        }
    }

    enemies = std::move(nuevaGeneracion);
}


int Wave::getGeneration() const { // Devuelve la generación actual
    return generation;
}

