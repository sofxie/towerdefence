//
// Created by ariel on 14/5/2025.
//

#ifndef TORRE_H
#define TORRE_H
#include "Enemigos/EnemyController.h"
#include <memory>
#include <vector>
using namespace std;

class Torre {
protected:
    std::pair<int, int> position;
public:
    virtual int Atacar() = 0;
    virtual void SubirNivel() = 0;
    virtual void AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) = 0;
    virtual int DistanciaAtaque() = 0;

    void setPosicion(int x, int y) {
        position = {x, y};
    }

    std::pair<int, int> getPosicion() const {
        return position;
    }

    virtual ~Torre() = default;    // Destructor virtual para permitir herencia segura
};

#endif //TORRE_H
