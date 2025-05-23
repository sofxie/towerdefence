#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include <memory>
#include "Map.h"
#include "Enemy.h"
#include <vector>
#include <utility>
#include <memory>
#include "Const.h"



using namespace std;

class EnemyController {
private:
    shared_ptr<Enemy> enemy;
    vector<pair<int, int>> path; // Ruta generada por A*
    int currentStep; // Paso actual en la ruta
    int x, y; // Posición actual en la grilla


public:
    EnemyController(shared_ptr<Enemy> e, int startX, int startY);

    void calculatePath(Map& map, int grid[ROW][COL], pair<int, int> dest);
    void move();
    shared_ptr<Enemy> getEnemy() const;
    void setPath(const std::vector<std::pair<int, int>>& nuevaRuta);
    pair<int, int> getPosition() const;

};

#endif // ENEMYCONTROLLER_H

