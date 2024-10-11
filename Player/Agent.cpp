#include <iostream>
#include <vector>
#include <string>
#include <random>

//#include "Objects/Ship.cpp"
#include "Agent.h"
#include "../Objects/Grid.h"
#include "Iplayer.h"
#include "Player.h"
#include "../Game.h"

using namespace std;

Agent::Agent(string name) : name(name){}

void Agent::placeShips(){
    vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {0, 2}, false),Ship(3, {0, 4}, false),Ship(4, {0, 6}, false),Ship(5, {0, 8}, false)};
    for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i),i+1);}
}

void Agent::attack(IPlayer* player){
    int X,Y;
    X=rand()%10;Y=rand()%10;
    do{
        X=rand()%10;Y=rand()%10;
    }while(player->grid.grid[Y][X] == 'O' || player->grid.grid[Y][X] == 'X');
    if (player->isTouched({Y,X})){
        player->grid.vieShips[(player->grid.grid[Y][X]-'0')-1]-=1;
        player->grid.isSunk((player->grid.grid[Y][X]-'0')-1);
        player->grid.grid[Y][X] = 'X';
        this->play.grid[Y][X]='X';
        cout << "Touché !" << endl;
    }
    else {
        player->grid.grid[Y][X] = 'O';
        this->play.grid[Y][X]='O';
        cout << "Dans l'eau !" << endl;
    }
}

void Agent::getEnvironment(){
    grid.display();
}
string Agent::getName() const{
    return name;
}
bool Agent::isTouched(pair<int,int>coordinates){
    if (grid.grid[coordinates.first][coordinates.second] == '~')return false;
    if (grid.grid[coordinates.first][coordinates.second] == 'O')return false;
    if (grid.grid[coordinates.first][coordinates.second] == 'X')return false;
    return true;
}