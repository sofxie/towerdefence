#include "EnemyController.h"

using namespace std;

EnemyController::EnemyController(::shared_ptr<Enemy> e, int startX, int startY)
    : enemy(e), x(startX), y(startY), currentStep(0) {}

void EnemyController::calculatePath(Map& map, int grid[ROW][COL], std::pair<int, int> dest) {
    path = map.getPath(grid, std::make_pair(x, y), dest);
    currentStep = 0;
}

void EnemyController::move() {
    if (currentStep < path.size()) {
        x = path[currentStep].first;
        y = path[currentStep].second;
        currentStep++;
    }
}

// Obtener enemigo en una lista
std::shared_ptr<Enemy> EnemyController::getEnemy() const {
    return enemy;
}
std::pair<int, int> EnemyController::getPosition() const {
    return { x, y };
}

void EnemyController::setPath(const std::vector<std::pair<int, int>>& nuevaRuta) {
    // Buscar el paso más cercano en la nueva ruta al enemigo
    int mejorPaso = 0;
    float menorDistancia = std::numeric_limits<float>::max();

    for (int i = 0; i < nuevaRuta.size(); ++i) {
        float dx = static_cast<float>(nuevaRuta[i].first - x);
        float dy = static_cast<float>(nuevaRuta[i].second - y);
        float distancia = dx * dx + dy * dy;  // Distancia al cuadrado

        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            mejorPaso = i;
        }
    }

    path = nuevaRuta;
    currentStep = mejorPaso;
}
