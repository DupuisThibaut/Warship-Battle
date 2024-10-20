#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "../Objects/Grid.h"
//Interface IPlayer qui représente un joueur (IA ou humain)
using namespace std;
#ifndef IPLAYER_H
#define IPLAYER_H
class IPlayer{
    public:
    // Grilles de placement et de jeu
    Grid grid;
    Grid play;
    //Fonction qui permet au joueur de placer ses bateaux sur la grille grid
        virtual void placeShips()=0;
    //Fonction permettant d'attaquer la grille adverse
        virtual void attack(IPlayer* opponent) = 0;
    //Getteur pour le nom du joueur
        virtual string getName() const = 0;
    //Fonction qui détermine si un bateau est touché aux coordonnées choisies
        virtual bool isTouched(pair<int,int>coordinates) = 0;
    //Fonction qui renvoie la grille de placement grid
        virtual void getEnvironment() = 0;
    //Fonction qui permet d'afficher les grilles de placement et de jeu
        void display(){cout<<"Bateau de " << getName() <<endl;grid.display();cout<<"Tir précédent de " << getName() <<endl;play.display();}
    //Constructeur de la classe IPlayer
        virtual ~IPlayer(){}
};
#endif