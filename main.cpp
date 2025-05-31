#include "CONTROLADOR/Controler.h"
#include "Enemigos/EnemyController.h"
#include <memory>
#include <vector>

int main() {
    std::vector<std::shared_ptr<EnemyController>> enemigos;
    Controler game(enemigos);
    game.run();
    return 0;
}