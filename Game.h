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
        // Grid grid;
        // grid.display();
        // Ship s1=Ship(2,pair<int,int>(1,1),false);
        // grid.placeShip(s1, 1);
        // grid.display();
        // Ship s2=Ship(3,pair<int,int>(1,3),false);
        // grid.placeShip(s2, 2);
        // grid.display();
        // Ship s3=Ship(3,pair<int,int>(1,5),false);
        // grid.placeShip(s3, 3);
        // grid.display();
        // Ship s4=Ship(4,pair<int,int>(1,7),false);
        // grid.placeShip(s4, 4);
        // grid.display();
        // Ship s5=Ship(5,pair<int,int>(8,1),true);
        // grid.placeShip(s5, 5);
        // grid.display();
        // char k;cin>>k;
        cout << "Placement des bateaux pour " << player1->getName() << endl;
        player1->placeShips();
        cout << "Placement des bateaux pour " << player2->getName() << endl;
        player2->placeShips();
        cout << "Lancement de la partie : ";
        //char i; cin >> i;
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