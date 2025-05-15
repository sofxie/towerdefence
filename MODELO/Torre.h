//
// Created by ariel on 14/5/2025.
//

#ifndef TORRE_H
#define TORRE_H
class Torre {
public:
    virtual int Atacar() = 0;
    virtual void SubirNivel() = 0;
    virtual void TipoDamage() = 0;
    virtual int DistanciaAtaque() = 0;

    virtual ~Torre() = default;    // Destructor virtual para permitir herencia segura
};

#endif //TORRE_H
