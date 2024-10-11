#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Ship.h"

using namespace std;
#ifndef GRID_H
#define GRID_H
class Grid {
public:
    vector<vector<char> > grid;
    vector<Ship> ships;
    vector<int> vieShips;

    Grid();

    bool placeShip(Ship ship, int numero) ;

    void display();

    void isSunk(int numero);

    bool allSunk();
};
#endif