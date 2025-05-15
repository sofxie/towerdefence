#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "../Map.h"
#include "Enemy.h"
#include <vector>
#include <utility>

class EnemyController {
private:
    Enemy* enemy;
    std::vector<std::pair<int, int>> path; // Ruta generada por A*
    int currentStep; // Paso actual en la ruta
    int x, y; // Posición actual en la grilla

public:
    EnemyController(Enemy* e, int startX, int startY);

    void calculatePath(Map& map, int grid[ROW][COL], std::pair<int, int> dest);
    void move();
    std::pair<int, int> getPosition() const;
};

#endif // ENEMYCONTROLLER_H

