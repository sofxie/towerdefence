#include "Enemy.h"


// Implementación de la clase base Enemy
Enemy::Enemy(int hp, float spd, int arRes, int mgRes, int artRes, EnemyType t)
    : health(hp), speed(spd), arrowResistance(arRes),
      magicResistance(mgRes), artilleryResistance(artRes), type(t), YaCobradoOro(false) {}

int Enemy::getHealth() const { return health; } // Obtener vida
float Enemy::getSpeed() const { return speed; } // Obtener velocidad
void Enemy::setSpeed(float spd) { speed = spd; } // Cambiar velocidad
int Enemy::getArrowResistance() const { return arrowResistance; } // Obtener resistencia a flechas
int Enemy::getMagicResistance() const { return magicResistance; } // Obtener resistencia a magia
int Enemy::getArtilleryResistance() const { return artilleryResistance; } // Obtener resistencia a artillería
EnemyType Enemy::getType() const { return type; } // Obtener tipo de enemigo
bool Enemy::GetEstadoCobrado() {
    return YaCobradoOro;
}

void Enemy::Cobrar() {
    YaCobradoOro = true;
}
bool Enemy::GetDestino() {
    return LlegaDestino;
}

void Enemy::Destino() {
    LlegaDestino = true;
}

void Enemy::takeDamage(int dmg, int type2) { // Reducción de vida
    if (type2 == 1) {
        std::cout << "Vida " << health << std::endl;
        health -= dmg * (100 - arrowResistance) / 100;
    }
    else if (type2 == 2) {
        std::cout << "Vida " << health << std::endl;
        health -= dmg * (100 - magicResistance) / 100;
    }
    else if (type2 == 3) {
        std::cout << "Vida " << health << std::endl;
        health -= dmg * (100 - artilleryResistance) / 100;
    }
}

bool Enemy::isAlive() const { // Comprobar si el enemigo está vivo
    return health > 0;
}

// Implementación de las clases derivadas de los enemigos con sus caracteristicas
Ogre::Ogre()
    : Enemy(
        // HP aleatorio
        []() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> hp_dist(230, 255);
            return hp_dist(gen);
        }(),

        // Speed aleatorio entre 8.0f y 13.0f
        []() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> spd_dist(8.0f, 13.0f);
            return spd_dist(gen);
        }(),

        // Valores fijos para el resto de parámetros
        20,
        5,
        5,
        EnemyType::Ogre
    ) {}

// Constructor con parámetros personalizados
Ogre::Ogre(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::Ogre) {}

DarkElf::DarkElf()
    : Enemy(
        []() { // HP aleatorio (80-120)
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(100, 125);
            return dist(gen);
        }(),
        []() { // Speed aleatorio (13.0f-18.0f)
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist(35.0f, 40.0f);
            return dist(gen);
        }(),
        5, 20, 5, EnemyType::DarkElf
    ) {}

DarkElf::DarkElf(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::DarkElf) {}

Harpy::Harpy()
    : Enemy(
        []() { // HP aleatorio (60-120)
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(80, 135);
            return dist(gen);
        }(),
        []() { // Speed aleatorio (18.0f-22.0f)
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist(20.0f, 25.0f);
            return dist(gen);
        }(),
        10, 5, 20, EnemyType::Harpy
    ) {}

// Nota: Corregí un typo (bp -> hp en el constructor parametrizado)
Harpy::Harpy(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::Harpy) {}

Mercenary::Mercenary()
    : Enemy(
        []() { // HP aleatorio (60-100)
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(100, 115);
            return dist(gen);
        }(),
        []() { // Speed aleatorio (13.0f-17.0f)
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist(15.0f, 20.0f);
            return dist(gen);
        }(),
        20, 5, 20, EnemyType::Mercenary
    ) {}

Mercenary::Mercenary(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::Mercenary) {}
