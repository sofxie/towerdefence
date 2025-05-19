#include "Enemy.h"

#include <iostream>

// Implementación de la clase base Enemy
Enemy::Enemy(int hp, float spd, int arRes, int mgRes, int artRes, EnemyType t)
    : health(hp), speed(spd), arrowResistance(arRes),
      magicResistance(mgRes), artilleryResistance(artRes), type(t) {}

int Enemy::getHealth() const { return health; }
float Enemy::getSpeed() const { return speed; }
int Enemy::getArrowResistance() const { return arrowResistance; }
int Enemy::getMagicResistance() const { return magicResistance; }
int Enemy::getArtilleryResistance() const { return artilleryResistance; }
EnemyType Enemy::getType() const { return type; }

void Enemy::takeArrowDamage(int dmg) {
    std::cout << "Vida " << health << std::endl;
    health -= dmg * (100 - arrowResistance) / 100;
}

void Enemy::takeMagicDamage(int dmg) {
    health -= dmg * (100 - magicResistance) / 100;
}

void Enemy::takeArtilleryDamage(int dmg) {
    health -= dmg * (100 - artilleryResistance) / 100;
}

bool Enemy::isAlive() const {
    return health > 0;
}


// Implementación de las clases derivadas
Ogre::Ogre() : Enemy(150, 20.5f, 20, 10, 30, EnemyType::Ogre) {}
Ogre::Ogre(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::Ogre) {}

DarkElf::DarkElf() : Enemy(300, 25.5f, 40, 60, 20, EnemyType::DarkElf) {}
DarkElf::DarkElf(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::DarkElf) {}

Harpy::Harpy() : Enemy(250, 30.0f, 60, 30, 10, EnemyType::Harpy) {}
Harpy::Harpy(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::Harpy) {}

void Harpy::takeArtilleryDamage(int dmg) {
    // Las harpías son más vulnerables al daño de artillería
    health -= dmg * (100 - (artilleryResistance/2)) / 100;
}

Mercenary::Mercenary() : Enemy(120, 35.0f, 30, 30, 30, EnemyType::Mercenary) {}
Mercenary::Mercenary(int hp, float spd, int arRes, int mgRes, int artRes)
    : Enemy(hp, spd, arRes, mgRes, artRes, EnemyType::Mercenary) {}
