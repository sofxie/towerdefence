#include "Wave.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>

Wave::Wave(int gen) : generation(gen), timesGetEnemiesCalled(0) {
    spawnEnemies();
}

void Wave::spawnEnemies() {
    enemies.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3);

    int baseEnemies = 10 + ((generation / 2) * 5); // 10 + 5 por cada 2 generaciones

    for (int i = 0; i < baseEnemies; ++i) {
        switch (dist(gen)) {
            case 0: enemies.push_back(std::make_unique<Ogre>()); break;
            case 1: enemies.push_back(std::make_unique<DarkElf>()); break;
            case 2: enemies.push_back(std::make_unique<Harpy>()); break;
            case 3: enemies.push_back(std::make_unique<Mercenary>()); break;
        }
    }

    printEnemiesInfo();
}

void Wave::evolve() {
    generation++;

    // 1. Guardar estadísticas actuales para comparación
    std::map<EnemyType, std::vector<float>> currentStats;
    for (const auto& enemy : enemies) {
        EnemyType type = enemy->getType();
        currentStats[type].push_back(enemy->getHealth());
        currentStats[type].push_back(enemy->getSpeed());
        currentStats[type].push_back(enemy->getArrowResistance());
        currentStats[type].push_back(enemy->getMagicResistance());
        currentStats[type].push_back(enemy->getArtilleryResistance());
    }

    // 2. Proceso de evolución
    std::map<EnemyType, std::vector<Enemy*>> enemiesByType;
    for (auto& e : enemies) {
        enemiesByType[e->getType()].push_back(e.get());
    }

    std::vector<std::unique_ptr<Enemy>> newGeneration;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> variation(-0.1f, 0.1f); // Variación aleatoria

    for (auto& [type, group] : enemiesByType) {
        if (group.empty()) continue;

        // Seleccionar los 2 mejores enemigos
        std::sort(group.begin(), group.end(), [](Enemy* a, Enemy* b) {
            return (a->getHealth() + a->getSpeed()) > (b->getHealth() + b->getSpeed());
        });

        Enemy* best = group[0];
        Enemy* secondBest = group.size() > 1 ? group[1] : best;

        // Número de descendientes basado en generación
        int offspringCount = 3 + (generation % 4); // Entre 3-6

        for (int i = 0; i < offspringCount; ++i) {
            // Mezclar características de los padres
            float mixRatio = 0.3f + variation(gen); // 20-40% de mezcla

            int health = static_cast<int>((best->getHealth() * (1.0f - mixRatio) +
                                        (secondBest->getHealth() * mixRatio)));
            float speed = (best->getSpeed() * (1.0f - mixRatio)) +
                         (secondBest->getSpeed() * mixRatio);

            // Aplicar mejoras generacionales
            health *= (1.05f + (generation * 0.02f)); // +5% base +2% por generación
            speed *= (1.03f + (generation * 0.01f));  // +3% base +1% por generación

            // Mejorar resistencias con límite máximo
            auto improveResistance = [](int res, int gen) {
                return std::min(95, res + static_cast<int>(res * 0.05f) + gen);
            };

            int arRes = improveResistance((best->getArrowResistance() + secondBest->getArrowResistance()) / 2, generation);
            int mgRes = improveResistance((best->getMagicResistance() + secondBest->getMagicResistance()) / 2, generation);
            int artRes = improveResistance((best->getArtilleryResistance() + secondBest->getArtilleryResistance()) / 2, generation);

            // Crear nuevo enemigo mejorado
            std::unique_ptr<Enemy> offspring;
            switch(type) {
                case EnemyType::Ogre:
                    offspring = std::make_unique<Ogre>(health, speed, arRes, mgRes, artRes);
                    break;
                case EnemyType::DarkElf:
                    offspring = std::make_unique<DarkElf>(health, speed, arRes, mgRes, artRes);
                    break;
                case EnemyType::Harpy:
                    offspring = std::make_unique<Harpy>(health, speed, arRes, mgRes, artRes);
                    break;
                case EnemyType::Mercenary:
                    offspring = std::make_unique<Mercenary>(health, speed, arRes, mgRes, artRes);
                    break;
            }

            newGeneration.push_back(std::move(offspring));
        }
    }

    enemies = std::move(newGeneration);

    // 3. Mostrar progreso de evolución
    std::cout << "\n=== EVOLUCION GENERACION " << generation << " ===" << std::endl;
    printEvolutionProgress(currentStats);
    printEnemiesInfo();
}

// Funcion que imprime el progreso de la evolucion
void Wave::printEvolutionProgress(const std::map<EnemyType, std::vector<float>>& currentStats) const {
    if (!previousStats.empty()) {
        std::cout << "Mejoras respecto a generacion anterior:\n";

        for (const auto& [type, stats] : currentStats) {
            float prevHealth = std::accumulate(previousStats[type].begin(),
                                            previousStats[type].end(), 0.0f) /
                                            (previousStats[type].size()/5);
            float currHealth = std::accumulate(stats.begin(), stats.end(), 0.0f) /
                             (stats.size()/5);

            float healthImprovement = ((currHealth - prevHealth) / prevHealth) * 100;

            std::cout << Enemy::typeToString(type) << "s:\n";
            std::cout << "  Salud: +" << std::fixed << std::setprecision(1) << healthImprovement << "%\n";
            // ... similar para otras estadísticas ...
        }
    }
    previousStats = currentStats;
}

// Funcion que imprime la información de los enemigos generados
void Wave::printEnemiesInfo() const {
    std::map<EnemyType, std::vector<std::string>> enemyDetails;
    std::map<EnemyType, int> typeCounts;

    for (const auto& enemy : enemies) {
        EnemyType type = enemy->getType();
        typeCounts[type]++;

        std::ostringstream oss;
        oss << Enemy::typeToString(type) << " ["
            << "HP:" << enemy->getHealth() << "|"
            << "SPD:" << std::fixed << std::setprecision(1) << enemy->getSpeed() << "|"
            << "AR:" << enemy->getArrowResistance() << "%|"
            << "MR:" << enemy->getMagicResistance() << "%|"
            << "ART:" << enemy->getArtilleryResistance() << "%]";

        enemyDetails[type].push_back(oss.str());
    }

    std::cout << "\nComposicion de la oleada:\n";
    for (const auto& [type, count] : typeCounts) {
        std::cout << "\n" << Enemy::typeToString(type) << "s (" << count << "):\n";
        for (const auto& desc : enemyDetails[type]) {
            std::cout << "  " << desc << "\n";
        }
    }
    std::cout << "\n================================\n";
}

// Versión no-const (puede modificar el vector)
std::vector<std::unique_ptr<Enemy>>& Wave::getEnemies() {
    std :: cout << "Llamada a getEnemies()\n";
    //imprimir el contador de llamadas
    std ::cout << "Contador de llamadas a getEnemies(): " << timesGetEnemiesCalled << std::endl;
    // Incrementar el contador de llamadas
    timesGetEnemiesCalled++;

    if (timesGetEnemiesCalled == 2) {
        evolve();
    }

    return enemies;
}

// Versión const (solo para lectura)
const std::vector<std::unique_ptr<Enemy>>& Wave::getEnemies() const {
    std ::cout << "Llamada a getEnemies() en modo const\n";
    return enemies;
}

int Wave::getGeneration() const {
    return generation;
}
