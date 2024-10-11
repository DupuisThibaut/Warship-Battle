#include <iostream>
#include <vector>
#include <string>
#include <random>

//#include "Objects/Ship.cpp"
#include "Objects/Grid.h"
#include "Player/IPlayer.h"
#include "Player/Player.h"
#include "Player/Agent.cpp"
#include "Game.h"

using namespace std;

Game::Game(IPlayer* p1, IPlayer* p2) : player1(p1), player2(p2) {}

void Game::start() {
    cout << "Placement des bateaux pour " << player1->getName() << endl;
    player1->placeShips();
    cout << "Placement des bateaux pour " << player2->getName() << endl;
    player2->placeShips();
    cout << "Lancement de la partie : ";
    char i; cin >> i;
}

IPlayer* Game::getPlayer(int x) const{
    if(x==1) return player1;
    return player2;
}

void Game::setFin(bool f){
    fin=f;
}
