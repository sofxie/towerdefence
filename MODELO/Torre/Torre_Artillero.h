//
// Created by sofia on 2025/5/18.
//

#ifndef TORRE_ARTILLERO_H
#define TORRE_ARTILLERO_H
#include "Torre.h"


class Torre_Artillero: public Torre {
    private:
        int nivel;
        int Enfriamiento;
        int DistanciaDeAtaque;
        int EnfriamientoEspecial;
        int TipoAtaque;
        std::pair<int, int> position;

public:
    // Constructor por defecto
    Torre_Artillero();

    int Atacar() override;
    void SubirNivel() override;
    void AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) override;
    int DistanciaAtaque() override;
    void setPosition(int x, int y) override;

    int GetNivel() override;

    std::pair<int, int> getPosicion() override;
    int AtaqueEspecial();
};



#endif //TORRE_ARTILLERO_H
