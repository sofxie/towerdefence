 #ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <sstream>
#include <random>
#include <iostream>

enum class EnemyType { Ogre, DarkElf, Harpy, Mercenary };

class Enemy {
protected: // Atributos de la clase(Caracterisrticas de los enemigos)
    int health;
    float speed;
    int arrowResistance;
    int magicResistance;
    int artilleryResistance;
    EnemyType type;
    bool YaCobradoOro;

public:

    Enemy(int hp, float spd, int arRes, int mgRes, int artRes, EnemyType t);
    virtual ~Enemy() = default;

    // Getters (accesores de los atributos)
    int getHealth() const;
    float getSpeed() const;
    void setSpeed(float spd);
    int getArrowResistance() const;
    int getMagicResistance() const;
    int getArtilleryResistance() const;
    EnemyType getType() const;

    // Reducción de vida. Según el daño que recibe el enemigo
    virtual void takeDamage(int dmg, int type);

    bool isAlive() const;

    virtual void Cobrar();
    virtual bool GetEstadoCobrado();

    virtual std::string getFullDescription() const { // Descripción completa del enemigo
        std::ostringstream oss;
        oss << typeToString(type) << " ["
            << "HP: " << health << ", "
            << "SPD: " << speed << ", "
            << "AR: " << arrowResistance << "%, "
            << "MR: " << magicResistance << "%, "
            << "ART: " << artilleryResistance << "%]";
        return oss.str();
    }

    static std::string typeToString(EnemyType type) { // Convertir tipo a string
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
};

class Mercenary : public Enemy {
public:
    Mercenary();
    Mercenary(int hp, float spd, int arRes, int mgRes, int artRes); // Nuevo
};


#endif
