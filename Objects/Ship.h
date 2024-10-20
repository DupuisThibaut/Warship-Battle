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
    //Taille (en nombre de cases) du bateau
    int size;
    //Booléen indiquant si le bateau est coulé
    bool isSunk;
    //Coordonnées du bateau
    pair<int, int> coordinates;
    //Booléen qui détermine l'orientation du bateau
    bool isVertical;
    //Constructeur de la classe bateau
    Ship(int size, pair<int, int> coordinates, bool isVertical);
    //Fonction de placement du bateau
    void placeShip(pair<int, int> coords, bool isVertical);
    //Getteur pour la taille du bateau
    int getSize();
    //Getteur pour l'orientation
    bool getIsVertical();
    //Getteur pour les coordonnées
    pair<int, int> getCoordinates();
    //Getteur pour l'état du bateau
    bool getSunk();
};
#endif //SECONDFILE_H