#include "Wave.h"


Wave::Wave(int gen) : generation(gen), timesGetEnemiesCalled(0) {
    spawnEnemies();
}

void Wave::spawnEnemies() { // Generar enemigos
    enemies.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 3); // 0 a 3 (4 tipos de enemigos)

    int baseEnemies = 2 + ((generation / 2) * 2); // 4 + 2 por cada 2 generaciones

    for (int i = 0; i < baseEnemies; ++i) {
        switch (dist(gen)) { // Generar enemigos aleatorios
            case 0: enemies.push_back(std::make_unique<Ogre>()); break; // Ogre
            case 1: enemies.push_back(std::make_unique<DarkElf>()); break; // DarkElf
            case 2: enemies.push_back(std::make_unique<Harpy>()); break; // Harpy
            case 3: enemies.push_back(std::make_unique<Mercenary>()); break; // Mercenary
        }
        totalEnemies += baseEnemies;
    }

    printEnemiesInfo();
    waveSpawnCount++; // Actualizar el contador de oleadas
}

void Wave::evolve() {
    // Incrementar el contador de generación
    generation++;
    waveSpawnCount++; // Actualizar el contador de oleadas
    mutationCount++; // Incrementar el contador de mutaciones

    // ------------------------------------------------------------
    // 1. ANÁLISIS DE LA GENERACIÓN ACTUAL (para comparación posterior)
    // ------------------------------------------------------------
    std::map<EnemyType, std::vector<float>> currentStats;
    for (const auto& enemy : enemies) {
        EnemyType type = enemy->getType();
        // Almacenamos todas las estadísticas importantes de cada enemigo
        currentStats[type].push_back(enemy->getHealth());
        currentStats[type].push_back(enemy->getSpeed());
        currentStats[type].push_back(enemy->getArrowResistance());
        currentStats[type].push_back(enemy->getMagicResistance());
        currentStats[type].push_back(enemy->getArtilleryResistance());
    }

    // ------------------------------------------------------------
    // 2. PROCESO DE EVOLUCIÓN PRINCIPAL
    // ------------------------------------------------------------
    std::map<EnemyType, std::vector<Enemy*>> enemiesByType;

    // Agrupar enemigos por tipo para evolución específica
    for (auto& e : enemies) {
        enemiesByType[e->getType()].push_back(e.get());
    }

    std::vector<std::unique_ptr<Enemy>> newGeneration;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Rango de variación para características (10% a 20% de variación)
    std::uniform_real_distribution<float> variation(1.1f, 1.2f);

    // Procesar cada tipo de enemigo por separado
    for (auto& [type, group] : enemiesByType) {
        if (group.empty()) continue;

        // --------------------------------------------------------
        // 2.1 SELECCIÓN NATURAL (elegir los mejores especímenes)
        // --------------------------------------------------------
        std::sort(group.begin(), group.end(), [](Enemy* a, Enemy* b) {
            // Criterio de fitness: salud + velocidad
            return (a->getHealth() + a->getSpeed()) > (b->getHealth() + b->getSpeed());
        });

        Enemy* best = group[0];                     // El mejor enemigo
        Enemy* secondBest = group.size() > 1 ? group[1] : best;  // El segundo mejor

        // --------------------------------------------------------
        // 2.2 REPRODUCCIÓN (crear nueva generación)
        // --------------------------------------------------------
        // Número de descendientes aumenta con las generaciones
        int offspringCount = 1 + (generation % 2);

        for (int i = 0; i < offspringCount; ++i) {
            // ----------------------------------------------------
            // 2.2.1 HERENCIA (combinar características de los padres)
            // ----------------------------------------------------
            float mixRatio = 0.3f * variation(gen); // 33%-36% de mezcla

            // Salud: combinación de padres + mejora generacional
            int health = static_cast<int>(
                (best->getHealth() * (1.0f - mixRatio)) +
                (secondBest->getHealth() * mixRatio)
            ) * (1.05f + (generation * 0.02f)); // +5% base +2% por generación

            // Velocidad: combinación de padres + mejora generacional
            float speed = (
                (best->getSpeed() * (1.0f - mixRatio)) +
                (secondBest->getSpeed() * mixRatio)
            ) * (1.03f + (generation * 0.01f)); // +3% base +1% por generación

            // ----------------------------------------------------
            // 2.2.2 MEJORA DE RESISTENCIAS
            // ----------------------------------------------------
            auto improveResistance = [](int res, int gen) {
                // Mejora compuesta: 5% + 1 punto por generación (máx 95%)
                return std::min(95, res + static_cast<int>(res * 0.05f) + gen);
            };

            // Calculamos resistencias mejoradas
            int arRes = improveResistance(
                (best->getArrowResistance() + secondBest->getArrowResistance()) / 2,
                generation
            );

            int mgRes = improveResistance(
                (best->getMagicResistance() + secondBest->getMagicResistance()) / 2,
                generation
            );

            int artRes = improveResistance(
                (best->getArtilleryResistance() + secondBest->getArtilleryResistance()) / 2,
                generation
            );

            // ----------------------------------------------------
            // 2.2.3 CREACIÓN DEL NUEVO ENEMIGO MEJORADO
            // ----------------------------------------------------
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
                    // Harpías podrían tener modificadores especiales aquí
                    break;
                case EnemyType::Mercenary:
                    offspring = std::make_unique<Mercenary>(health, speed, arRes, mgRes, artRes);
                    break;
            }

            // Añadir el nuevo enemigo a la generación
            newGeneration.push_back(std::move(offspring));
            totalEnemies++;
        }


    }

    // ------------------------------------------------------------
    // 3. ACTUALIZACIÓN FINAL
    // ------------------------------------------------------------
    // Reemplazar la generación anterior con la nueva
    enemies = std::move(newGeneration);

    // ------------------------------------------------------------
    // 4. REPORTE DE EVOLUCIÓN
    // ------------------------------------------------------------
    std::cout << "\n=== EVOLUCIÓN GENERACIÓN " << generation << " ===" << std::endl;
    std::cout << "Mejoras aplicadas:\n";
    std::cout << "- Salud: +" << (5 + generation * 2) << "% (base)\n";
    std::cout << "- Velocidad: +" << (3 + generation * 1) << "% (base)\n";
    std::cout << "- Resistencias: +5% +" << generation << " puntos (máx 95%)\n";

    currentStats = std::move(currentStats); // actualiza la variable miembro

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

    if (timesGetEnemiesCalled == 3) {
        evolve();
    }

    return enemies;
}

// Versión const (solo para lectura)
const std::vector<std::unique_ptr<Enemy>>& Wave::getEnemies() const {
    std ::cout << "Llamada a getEnemies() en modo const\n";
    return enemies;
}

int Wave::getGeneration() const { // Obtener la generación actual
    return generation;
}

int Wave::getMutationCount() const {
    return mutationCount;
}


int Wave::getTotalEnemiesCreated() const {
    return totalEnemies;
}

int Wave::getWaveSpawnCount() const {
    static bool firstCall = true;
    if (firstCall) {
        firstCall = false;
        return waveSpawnCount - 1;
    }
    else {
        return waveSpawnCount;
    }
}



std::vector<std::string> Wave::getEnemiesStats() const {
    std::vector<std::string> statsList;
        for (const auto& enemy : enemies) {
            std::ostringstream oss;
            oss << Enemy::typeToString(enemy->getType()) << " "
                << "HP: " << enemy->getHealth() << ", "
                << "SD: " << std::fixed << std::setprecision(1) << enemy->getSpeed() << ", "
                << "AR: " << enemy->getArrowResistance() << "%, "
                << "MR: " << enemy->getMagicResistance() << "%, "
                << "ATR: " << enemy->getArtilleryResistance() << "%";
            statsList.push_back(oss.str());
        }
        return statsList;

    }




