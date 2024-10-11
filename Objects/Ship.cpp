#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Ship.h"
using namespace std;

// Classe Ship représentant un bateau
Ship::Ship(int size, pair<int, int> coordinates, bool isVertical) : size(size), coordinates(coordinates), isVertical(isVertical), isSunk(false) {}

void Ship::placeShip(pair<int, int> coords, bool isVertical) {
        coordinates = coords;
        this->isVertical = isVertical;
    }

int Ship::getSize() { return size; }

bool Ship::getIsVertical() { return isVertical; }

pair<int, int> Ship::getCoordinates() { return coordinates; }

bool Ship::getSunk(){return isSunk;}
