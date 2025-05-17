#ifndef ENEMY_H
#define ENEMY_H

#include <string>

enum class EnemyType { Ogre, DarkElf, Harpy, Mercenary };

class Enemy {
protected: // Atributos de la clase(Caracterisrticas de los enemigos)
    int health;
    float speed;
    int arrowResistance;
    int magicResistance;
    int artilleryResistance;
    EnemyType type;

public:
    Enemy(int hp, float spd, int arRes, int mgRes, int artRes, EnemyType t);
    virtual ~Enemy() = default;

    // Getters (accesores de los atributos)
    int getHealth() const;
    float getSpeed() const;
    int getArrowResistance() const;
    int getMagicResistance() const;
    int getArtilleryResistance() const;
    EnemyType getType() const;

    // Reducción de vida. Según el daño que recibe el enemigo
    virtual void takeArrowDamage(int dmg);
    virtual void takeMagicDamage(int dmg);
    virtual void takeArtilleryDamage(int dmg);

    bool isAlive() const;

    static std::string typeToString(EnemyType type) {
        switch(type) {
            case EnemyType::Ogre: return "Ogro";
            case EnemyType::DarkElf: return "Elfo Oscuro";
            case EnemyType::Harpy: return "Arpía";
            case EnemyType::Mercenary: return "Mercenario";
            default: return "Desconocido";
        }
    }
};

/*
 *Clases de los enemigos
 */
class Ogre : public Enemy {
public:
    Ogre(); // Constructor por defecto
    Ogre(int hp, float spd, int arRes, int mgRes, int artRes); // Nuevo
};

class DarkElf : public Enemy {
public:
    DarkElf();
    DarkElf(int hp, float spd, int arRes, int mgRes, int artRes); // Nuevo
};

class Harpy : public Enemy {
public:
    Harpy();
    Harpy(int hp, float spd, int arRes, int mgRes, int artRes); // Nuevo
    void takeArtilleryDamage(int dmg) override;
};

class Mercenary : public Enemy {
public:
    Mercenary();
    Mercenary(int hp, float spd, int arRes, int mgRes, int artRes); // Nuevo
};


#endif
