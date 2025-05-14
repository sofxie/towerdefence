#include "Map.h"

#include <float.h>
#include <ostream>
#include <iostream>
#include <stack>
#include <string.h>
#include <valarray>
#include <set>
#include <utility> // para Pair
#include <cmath> // libreria para operaciones mate

using namespace std;

// Ver si la celda (row, col) es valido o no
bool Map::isValid(int row, int col) {
    // return True si no sale del mapa
    return (row>=0) && (row<ROW) && (col>=0) && (col<COL);
}
// Revisar si hay paso
bool Map::isUnBlocked(int grid[][COL],int row, int col) {
    // return True si la celda es accesible
    if (grid[row][col]==1)
        return true;
    else
        // return False si no se puede acceder
        return false;
}
// Revisar si encontro destino final
bool Map::isDestination(int row, int col, Pair dest) {
    // return True si la celda es el destino
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}
// Calcula la heuristica
double Map::calculateHValue(int row, int col, Pair dest) {
    // return valor de la heuristica calculada
    return ((double)sqrt((row-dest.first)*(row-dest.first)+(col-dest.second)*(col-dest.second)));
}
// Trazar el camino
void Map::tracePath(cell cellDetails[][COL], Pair dest) {
    //cout<<"Camino:";
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d)", p.first, p.second);
    }
    return;
}
// Cambiar el valor del mapa al colocar torre
// Retorna true si se puede cambiar el valor
// False si la casilla no puede ser modificado
bool Map::blocked(int grid[][COL], int row, int col) {
    // return True si se puede
    if (grid[row][col]==1) {
        grid[row][col] = 0;
        return true;
    }else
        return false;
}
// Implementar el algoritmo
void Map::aEstrellita(int grid[][COL], Pair src, Pair dest) {
    // (No es tan necesario)
    // Si el inicio sale de la mapa
    if (isValid(src.first, src.second) == false) {
        printf("No solution\n");
        return;
    }
    // (No es tan necesario)
    // Si el final sale de la mapa
    if (isValid(dest.first, dest.second) == false) {
        printf("Destinarion no es valido");
        return;
    }
    // Si esta no hay paso
    if (isUnBlocked(grid, src.first, src.second) == false || isUnBlocked(grid, dest.first, dest.second) == false) {
        printf("No solution\n");
        return;
    }
    // Si ya encontro el destino
    if(isDestination(src.first, src.second, dest) == true) {
        printf("Ya destino");
        return;
    }
    // Crear una lista cerrada y rellenarlo con falso
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));
    // Declara un arreglo para guardar
    // datos de una celda (la tabla que hizo el profe)
    cell cellDetails[ROW][COL];

    // Indices de la celda (determina posicion)
    int i,j;

    for (i=0; i<ROW;i++) {
        for (j=0;j<COL;j++) {
            cellDetails[i][j].parent_i = i; // Posicion en x
            cellDetails[i][j].parent_j = j; // Posicion en y
            cellDetails[i][j].f = FLT_MAX; // Valor f (peso total)
            cellDetails[i][j].g = FLT_MAX; // Valor g (costo movimiento)
            cellDetails[i][j].h = FLT_MAX; // Valor h (Distancia de la celda actual al destino)
        }
    }

    // Inicializar los parametros del nodo inicial
    i = src.first;
    j = src.second;

    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;

    // Crear lista abierta que contiene informacion de la heuristica
    set <pPairs> openList;

    // Colocar la celda inicial en la lista (Iniciar)
    openList.insert(make_pair(0.0, make_pair(i,j)));

    // Iniciar como falso si el destino fue encontrado
    bool foundDest = false;

    // Bucle para recorrer las celdas del mapa
    while (!openList.empty()) {
        pPairs p = *openList.begin();

        // Quitar el vertice incial
        openList.erase(openList.begin());

        // Agregar vertice a la lista cerrada
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // para guardar g,h,f
        double gNew;
        double hNew;
        double fNew;

        // Aplicar logica de calculo de ruta
        // para cada direccion

        // Direccion Norte
        // Revisar si es valido
        if (isValid(i-1,j) == true) {
            // Revisar si la celda es el destino
            if (isDestination(i-1, j, dest) == true) {
                // Actualizar la informaciond de la celda actual
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                // Trazar la ruta
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // Si la celda esta bloqueada o recorrida, ignorar
            else if (closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true) {
                // Calcular heuristica
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i-1, j, dest);
                fNew = gNew + hNew;

                // Si no sale registrado como visitado
                // agregarlo a la lista
                if (cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i-1,j)));

                    // Actualizar detalles de la celda
                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }
        // Direccion Sur
        // Revisar si es valido
        if (isValid(i+1,j) == true) {
            // Revisar si la celda es el destino
            if (isDestination(i+1, j, dest) == true) {
                // Actualizar la informaciond de la celda actual
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                // Trazar la ruta
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // Si la celda esta bloqueada o recorrida, ignorar
            else if (closedList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true) {
                // Calcular heuristica
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                // Si no sale registrado como visitado
                // agregarlo a la lista
                if (cellDetails[i-1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i+1,j)));

                    // Actualizar detalles de la celda
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }
        // Direccion Oeste
        // Revisar si es valido
        if (isValid(i,j-1) == true) {
            // Revisar si la celda es el destino
            if (isDestination(i, j-1, dest) == true) {
                // Actualizar la informaciond de la celda actual
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                // Trazar la ruta
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // Si la celda esta bloqueada o recorrida, ignorar
            else if (closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true) {
                // Calcular heuristica
                gNew = cellDetails[i][j-1].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                // Si no sale registrado como visitado
                // agregarlo a la lista
                if (cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i,j-1)));

                    // Actualizar detalles de la celda
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
        // Direccion Este
        // Revisar si es valido
        if (isValid(i,j+1) == true) {
            // Revisar si la celda es el destino
            if (isDestination(i, j+1, dest) == true) {
                // Actualizar la informaciond de la celda actual
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                // Trazar la ruta
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // Si la celda esta bloqueada o recorrida, ignorar
            else if (closedList[i][j+1] == false && isUnBlocked(grid, i, j+1) == true) {
                // Calcular heuristica
                gNew = cellDetails[i][j+1].g + 1.0;
                hNew = calculateHValue(i, j+1, dest);
                fNew = gNew + hNew;

                // Si no sale registrado como visitado
                // agregarlo a la lista
                if (cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i,j+1)));

                    // Actualizar detalles de la celda
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }
    }
}