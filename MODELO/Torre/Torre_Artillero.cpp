//
// Created by sofia on 2025/5/18.
//

#include "Torre_Artillero.h"
#include <iostream>
#include <cmath>
using namespace std;

// Constructor por defecto
Torre_Artillero::Torre_Artillero()
    : nivel(1), Enfriamiento(2), DistanciaDeAtaque(3), EnfriamientoEspecial(10), TipoAtaque(1), position({-1, -1}){}

// Funcion para retornar cantidad de daño
int Torre_Artillero::Atacar() {
    int damage = 0;
    if (nivel == 1) {
        if (Enfriamiento == 0) {
            Enfriamiento = 8000;
            damage = 50;
        }
    }
    else if (nivel == 2) {
        if (Enfriamiento == 0) {
            Enfriamiento = 6000;
            damage = 100;
        }
    }
    else if (nivel == 3) {
        if (Enfriamiento == 0) {
            Enfriamiento = 4000;
            damage = 200;
        }
    }
    return damage;
}

// Retorna Distancia de Ataque
int Torre_Artillero::DistanciaAtaque() {
    return DistanciaDeAtaque;
}

// Sube de nivel a la torre
void Torre_Artillero::SubirNivel() {
  if (nivel < 3)
      nivel++;
  std::cout << "Torre de Artilleria sube al nivel " << nivel << "." << std::endl;
}

int Torre_Artillero::GetNivel() {
    return nivel;
}

// Funcion para Atacar enemigos en x distancia
// Toma como entrada la lista de enemigos
void Torre_Artillero::AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) {
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
        int dano = Atacar();  // Si está listo para atacar
        if (nivel == 1) {
                dano = 200;

        }
        else if (nivel == 2) {
                dano = 400;

        }
        else if (nivel == 3) {
                dano = 800;

        }



        // Si esta dentro del area, realizar ataque
        if (distancia <= DistanciaAtaque()) {

            if (enemigo->getEnemy()->getHealth() <= 0) {
            }
            else {
                if (EnfriamientoEspecial > 0) {
                    EnfriamientoEspecial--;
                }
                if (EnfriamientoEspecial <= 0) {
                    dano = 1000;
                    if (nivel == 1) {
                        EnfriamientoEspecial = 10;
                    }
                    else if (nivel == 2) {
                        EnfriamientoEspecial = 8;
                    }
                    else {
                        EnfriamientoEspecial = 5;
                    }
                }
                std::cout << dano << " dano realizado " << EnfriamientoEspecial << endl;
                if (dano > 0) {
                    enemigo->getEnemy()->takeDamage(dano, 2);  // Atacar al enemigo real
                    std::cout << "Torre Artilleria inflige " << dano << " de daño." << std::endl;  // Solo ataca una vez por ciclo
                    break;
                }
            }
        }
    }
}

void Torre_Artillero::setPosition(int x, int y) {
    position = {x, y};
}

std::pair<int, int> Torre_Artillero::getPosicion() {
    return position;
}

