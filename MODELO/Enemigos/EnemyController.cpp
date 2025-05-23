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


