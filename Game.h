#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Player/Iplayer.h"

using namespace std;
#ifndef GAME_H
#define GAME_H

using namespace std;
//Environnement :
class Game {
public:

    IPlayer* player1;
    IPlayer* player2;
    bool fin=false;
    //Constructeur de la classe Game
    Game(IPlayer* p1, IPlayer* p2) : player1(p1), player2(p2) {}
    //Fonction d'initialisation de l'environnement de jeu
    void start() {
        cout << "Placement des bateaux pour " << player1->getName() << endl;
        player1->placeShips();
        cout << "Placement des bateaux pour " << player2->getName() << endl;
        player2->placeShips();
        cout << "Lancement de la partie : ";
        char i; cin >> i;
    }
    //Fonction qui retourne un joueur afin de permettre l'accès à certaines informations
    IPlayer* getPlayer(int x) const{
        if(x==1) return player1;
        return player2;
    }
    //Fonction pour déclarer la fin de la partie
    void setFin(bool f){
        fin=f;
    }
};
#endif