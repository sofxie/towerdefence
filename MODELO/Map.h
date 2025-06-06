#ifndef MAP_H
#define MAP_H
#include "Const.h"
#include <utility>
#include <vector>

using namespace std;

typedef pair<int,int> Pair; //
typedef pair<double,pair<int,int>> pPairs; //
class Map {
private:
    struct cell {
        int parent_i; // Padre de x
        int parent_j; // Padre de y

        // Variables para formula calculo de f=g+h
        double f;
        double g;
        double h;
    };
public:
    Map() {} // Constructor
    // Revisa si la celda es valido o no
    bool isValid(int row, int col);
    // Revisa si hay algun obstaculo en el mapa
    bool isUnBlocked(int grid[][COL],int row, int col);
    // Revisa si ya llego al objetivo
    bool isDestination(int row, int col, Pair dest);
    // Funcion que calcula heuristic
    double calculateHValue(int row, int col, Pair dest);
    // Funcion de trazar la ruta
    void tracePath(cell cellDetails[][COL], Pair dest);
    // Funcion del Algoritmo A*
    bool aEstrellita(int grid[][COL], Pair scr, Pair dest);
    // Funcion para bloquear en el mapa
    bool blocked(int grid[][COL],int row,int col);
    // Funcion que le manda la ruta a los enemigos
    std::vector<Pair> lastPath;
    std::vector<Pair> getPath(int grid[][COL], Pair src, Pair dest);
};



#endif //MAP_H
