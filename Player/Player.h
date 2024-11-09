#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "../Objects/Ship.h"
#include "../Objects/Grid.h"
#include "Iplayer.h"
//Classe player qui étend IPlayer et qui désigne un vrai joueur
using namespace std;
#ifndef PLAYER_H
#define PLAYER_H

class Player : public IPlayer{
public:
    //Nom du joueur
    string name;
    //Constructeur de la classe Player
    Player(string name);
    //Implémentation de la fonction de placement pour le joueur
    void placeShips() override;
    //Fonction qui choisit d'attaquer ou défendre
    pair<int,int> whatToDo(IPlayer* player,pair<int,int> coordinates) override;
    //Implémentation de la fonction d'attaque pour le joueur
    pair<int,int> attack(IPlayer* player)override;
    //Implémentation de la détection de touché
    bool isTouched(pair<int,int>coordinates) override;
    //Implémentation du getteur de nom de joueur
    string getName() const override;
    //Setteur pour le nom du joueur
	void setName(string newName);
    //Implémentation de la fonction pour obtenir la grille grid
    void getEnvironment() override;
};
#endif