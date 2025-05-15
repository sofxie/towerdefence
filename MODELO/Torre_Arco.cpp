#include "Torre_Arco.h"
#include <iostream>

// Constructor por defecto
Torre_Arco::Torre_Arco()
    : nivel(1), Enfriamiento(2), DistanciaDeAtaque(5) {}


int Torre_Arco::Atacar() {
    int damage = 0;
    if (nivel == 1) {
        if (Enfriamiento == 0) {
            Enfriamiento = 10;
            damage = 3;
        }
    }
    else if (nivel == 2) {
        if (Enfriamiento == 0) {
            Enfriamiento = 8;
            damage = 6;
        }
    }
    else if (nivel == 3) {
        if (Enfriamiento == 0) {
            Enfriamiento = 6;
            damage = 12;
        }
    }
    else {
        Enfriamiento = Enfriamiento - 1;
    }
    return damage;
}

void Torre_Arco::SubirNivel() {
    nivel++;
    std::cout << "Torre de Arco sube al nivel " << nivel << "." << std::endl;
}

void Torre_Arco::TipoDamage() {
    std::cout << "Daño arquero." << std::endl;
}

int Torre_Arco::DistanciaAtaque() {
    return DistanciaDeAtaque;
}




