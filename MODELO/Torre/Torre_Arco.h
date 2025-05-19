//
// Created by ariel on 14/5/2025.
//

#ifndef TORRE_ARCO_H
#define TORRE_ARCO_H

#include "Torre.h"

class Torre_Arco : public Torre {
private:
    int nivel;
    int Enfriamiento;
    int DistanciaDeAtaque;
    int EnfriamientoEspecial;
    int TipoAtaque;
public:
    // Constructor por defecto
    Torre_Arco();

    int Atacar() override;
    void SubirNivel() override;
    void AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) override;
    int DistanciaAtaque() override;
    int AtaqueEspecial();

};

#endif //TORRE_ARCO_H