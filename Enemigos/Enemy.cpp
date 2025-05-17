#include "Enemy.h"

// Enemy base
Enemy::Enemy(int hp, float spd, int arRes, int mgRes, int artRes, EnemyType t)
    : health(hp), speed(spd), arrowResistance(arRes), magicResistance(mgRes), artilleryResistance(artRes), type(t) {}

int Enemy::getHealth() const { return health; }
float Enemy::getSpeed() const { return speed; }
int Enemy::getArrowResistance() const { return arrowResistance; }
int Enemy::getMagicResistance() const { return magicResistance; }
int Enemy::getArtilleryResistance() const { return artilleryResistance; }
EnemyType Enemy::getType() const { return type; }

// Reducción de vida. Según el daño que recibe el enemigo, ys estas son las funciónes que se encargan de reducir la vida del enemigo

void Enemy::takeArrowDamage(int dmg) { // Reducción de vida por flechas
    int actual = dmg - arrowResistance;
    if (actual > 0) health -= actual;
}

void Enemy::takeMagicDamage(int dmg) { // Reducción de vida por magia
    int actual = dmg - magicResistance;
    if (actual > 0) health -= actual;
}

void Enemy::takeArtilleryDamage(int dmg) { // Reducción de vida por artillería
    int actual = dmg - artilleryResistance;
    if (actual > 0) health -= actual;
}

void Enemy::setStats(int hp, int spd, int arRes, int mgRes, int artRes) { // Establece los atributos del enemigo
    health = hp;
    speed = spd;
    arrowResistance = arRes;
    magicResistance = mgRes;
    artilleryResistance = artRes;
}

bool Enemy::isAlive() const { return health > 0; } // Verifica si el enemigo está vivo

// Ogros
Ogre::Ogre()
    : Enemy(150, 15.0f, 20, 5, 5, EnemyType::Ogre) {}

// elfos Oscuros
DarkElf::DarkElf()
    : Enemy(100, 30.0f, 5, 20, 5, EnemyType::DarkElf) {}

// Harpias
Harpy::Harpy()
    : Enemy(80, 20.0f, 10, 10, 1000, EnemyType::Harpy) {}

void Harpy::takeArtilleryDamage(int dmg) {
    // Harpías no reciben daño de artillería
}

// Mercenarios
Mercenary::Mercenary()
    : Enemy(120, 25.5f, 20, 5, 20, EnemyType::Mercenary) {}
