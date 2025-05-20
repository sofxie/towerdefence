#include "Torre_Arco.h"
#include <iostream>
#include <cmath>
using namespace std;

// Constructor por defecto
Torre_Arco::Torre_Arco()
    : nivel(1), Enfriamiento(2), DistanciaDeAtaque(10), EnfriamientoEspecial(10), TipoAtaque(1), position({-1, -1}){}

// Funcion para retornar cantidad de daño
int Torre_Arco::Atacar() {
    std::cout << "Atacar" << std::endl;
    int damage = 0;
    if (nivel == 1) {
        if (Enfriamiento == 0) {
            Enfriamiento = 10;
            damage = 5;
        }
    }
    else if (nivel == 2) {
        if (Enfriamiento == 0) {
            Enfriamiento = 8;
            damage = 20;
        }
    }
    else if (nivel == 3) {
        if (Enfriamiento == 0) {
            Enfriamiento = 6;
            damage = 50;
        }
    }
    else {
        Enfriamiento = Enfriamiento - 1;
        return 0;
    }
    return damage;
}

// Retorna Distancia de Ataque
int Torre_Arco::DistanciaAtaque() {
    return DistanciaDeAtaque;
}

// Sube de nivel a la torre
void Torre_Arco::SubirNivel() {
  if (nivel < 3)
      nivel++;
  std::cout << "Torre de Arco sube al nivel " << nivel << "." << std::endl;
}

int Torre_Arco::GetNivel() {
    return nivel;
}

// Funcion para Atacar enemigos en x distancia
// Toma como entrada la lista de enemigos
void Torre_Arco::AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) {
    // Espera a que pase el cooldown
    if (Enfriamiento > 0) {
        Enfriamiento--;
        return;
    }
    // Por cada enemigo presente
    for (auto& enemigo : enemigos) {
        // Calcular area de ataque
        // 1. Obtengo su posicion
        auto [ex, ey] = enemigo->getPosition();
        // 2. Posición de la torre
        auto [row, col] = this->getPosicion();
        // 3. Calcular distancia entre los dos objetos
        float distancia = std::sqrt(std::pow(ex - row, 2) + std::pow(ey - col, 2));
        int dis = DistanciaAtaque();
        std::cout<<"Distancia Calculada:"<< distancia<<"Distancia"<<dis<<std::endl;
        int dano = Atacar();  // Si está listo para atacar

        // Si esta dentro del area, realizar ataque
        if (distancia <= DistanciaAtaque()) {
            if (dano > 0) {
                enemigo->getEnemy()->takeArrowDamage(dano);  // Atacar al enemigo real
                std::cout << "Torre Arco inflige " << dano << " de daño." << std::endl;
                break;  // Solo ataca una vez por ciclo
            }
        }
    }
}

void Torre_Arco::setPosition(int x, int y) {
    position = {x, y};
}

std::pair<int, int> Torre_Arco::getPosicion() {
    return position;
}

// Funcion para implementar Ataque especial
int Torre_Arco::AtaqueEspecial(){
    if (EnfriamientoEspecial == 0) {
        EnfriamientoEspecial = 10; // Reset de cooldown
        return 100; // Doble daño, por ejemplo
    } else {
        EnfriamientoEspecial--;
        return 0;
    }
}