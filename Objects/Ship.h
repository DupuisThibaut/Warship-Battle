#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;
#ifndef SHIP_H
#define SHIP_H
// Classe Ship représentant un bateau
class Ship {
public:
    int size;
    bool isSunk;
    pair<int, int> coordinates;
    bool isVertical;

    Ship(int size, pair<int, int> coordinates, bool isVertical);

    void placeShip(pair<int, int> coords, bool isVertical);

    int getSize();

    bool getIsVertical();

    pair<int, int> getCoordinates();

    bool getSunk();
};
#endif //SECONDFILE_H