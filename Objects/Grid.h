#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Ship.h"
//Cette classe modélise la grille sur laquelle le joueur place/attaque
using namespace std;
#ifndef GRID_H
#define GRID_H
class Grid {
public:
    //Liste modélisant le plateau de jeu
    vector<vector<char> > grid;
    //Liste des bateaux disponibles
    vector<Ship> ships;
    //Liste stockant le nombre de vies des bateaux
    vector<int> vieShips;
    //Constructeur de la classe Grid
    Grid();
    //Fonction pour placer un bateau
    bool placeShip(Ship ship, int numero) ;
    //Fonction d'affichage de la grille
    void display();
    //Fonction qui met à jour "vieShips" en fonction de l'état d'un bateau
    void isSunk(int numero);
    //Fonction qui renvoie si la partie est terminée (tout les bateaux ont coulé) ou non
    bool allSunk();
};
#endif