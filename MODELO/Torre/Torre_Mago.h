//
// Created by ariel on 20/5/2025.
//

#ifndef TORRE_MAGO_H
#define TORRE_MAGO_H
#include "Torre.h"

class Torre_Mago: public Torre {
private:
    int nivel;
    int Enfriamiento;
    int DistanciaDeAtaque;
    int EnfriamientoEspecial;
    int TipoAtaque;
    std::pair<int, int> position;
    bool AtaqueEspecialAct;

public:
    // Constructor por defecto
    Torre_Mago();

    int Atacar() override;
    void SubirNivel() override;
    void AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) override;
    int DistanciaAtaque() override;
    void setPosition(int x, int y) override;

    int GetNivel() override;

    std::pair<int, int> getPosicion() override;
    int AtaqueEspecial();
};




#endif //TORRE_MAGO_H
