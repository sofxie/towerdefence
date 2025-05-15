//
// Created by ariel on 14/5/2025.
//

#ifndef TORRE_ARCO_H
#define TORRE_ARCO_H

#include "Torre.h"

class Torre_Arco : public Torre {
private:
    int nivel = 0;
    int Enfriamiento = 0;
    int DistanciaDeAtaque = 0;

public:
    // Constructor por defecto
    Torre_Arco();

    int Atacar() override;
    void SubirNivel() override;
    void TipoDamage() override;
    int DistanciaAtaque() override;
};

#endif //TORRE_ARCO_H