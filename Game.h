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
    Game(IPlayer* p1, IPlayer* p2);
    //Fonction d'initialisation de l'environnement de jeu
    void start();
    //Fonction qui retourne un joueur afin de permettre l'accès à certaines informations
    IPlayer* getPlayer(int x) const;
    //Fonction pour déclarer la fin de la partie
    void setFin(bool f);
};
#endif