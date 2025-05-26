#include "Torre_Mago.h"
#include <iostream>
#include <cmath>
using namespace std;

// Constructor por defecto
Torre_Mago::Torre_Mago()
    : nivel(1), Enfriamiento(2), DistanciaDeAtaque(1), EnfriamientoEspecial(10), TipoAtaque(1), position({-1, -1}), AtaqueEspecialAct(false){}

// Funcion para retornar cantidad de daño
int Torre_Mago::Atacar() {
    int damage = 0;
    if (nivel == 1) {
        if (Enfriamiento == 0) {
            if (AtaqueEspecialAct) {
                Enfriamiento = 250;
            }
            else {
                Enfriamiento = 500;
            }
            damage = 5;
        }
    }
    else if (nivel == 2) {
        if (Enfriamiento == 0) {
            if (AtaqueEspecialAct) {
                Enfriamiento = 125;
            }
            else {
                Enfriamiento = 250;
            }
            damage = 10;
        }
    }
    else if (nivel == 3) {
        if (Enfriamiento == 0) {
            if (AtaqueEspecialAct) {
                Enfriamiento = 50;
            }
            else {
                Enfriamiento = 125;
            }

            damage = 20;
        }
    }
    return damage;
}

// Retorna Distancia de Ataque
int Torre_Mago::DistanciaAtaque() {
    return DistanciaDeAtaque;
}

// Sube de nivel a la torre
void Torre_Mago::SubirNivel() {
  if (nivel < 3)
      nivel++;
  std::cout << "Torre de Mago sube al nivel " << nivel << "." << std::endl;
}

int Torre_Mago::GetNivel() {
    return nivel;
}

// Funcion para Atacar enemigos en x distancia
// Toma como entrada la lista de enemigos
void Torre_Mago::AtacarEnemigo(std::vector<std::shared_ptr<EnemyController>>& enemigos) {
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
                dano = 20;

        }
        else if (nivel == 2) {
                dano = 40;

        }
        else if (nivel == 3) {
                dano = 80;

        }




        // Si esta dentro del area, realizar ataque
        if (distancia <= DistanciaAtaque()) {
            if (enemigo->getEnemy()->getHealth() <= 0) {
            }
            else {
                if (EnfriamientoEspecial > 0) {
                    EnfriamientoEspecial--;
                }
                if (EnfriamientoEspecial == 0) {
                    if (AtaqueEspecialAct) {
                        AtaqueEspecialAct = false;
                    }
                    else {
                        AtaqueEspecialAct = true;
                    }
                    if (nivel == 1) {
                        EnfriamientoEspecial = 15;
                    }
                    else if (nivel == 2) {
                        EnfriamientoEspecial = 10;
                    }
                    else {
                        EnfriamientoEspecial = 5;
                    }

                }
                std::cout << EnfriamientoEspecial << std::endl;
                if (dano > 0) {
                    enemigo->getEnemy()->takeDamage(dano, 3);  // Atacar al enemigo real
                    std::cout << "Torre Mago inflige " << dano << " de daño." << std::endl;  // Solo ataca una vez por ciclo
                    break;
                }
            }
        }
    }
}

void Torre_Mago::setPosition(int x, int y) {
    position = {x, y};
}

std::pair<int, int> Torre_Mago::getPosicion() {
    return position;
}

