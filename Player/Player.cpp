#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

#include "../Objects/Ship.h"
#include "../Objects/Grid.h"
#include "Player.h"

using namespace std;

Player::Player(string name) : name(name) {}

void Player::placeShips(){
    int X,Y;
    string V;
    bool VH=true;
    bool bonnePosition=true;
    string f;cout << "manuelle ?";cin >> f;if(f=="n"){
        vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {0, 2}, false),Ship(3, {0, 4}, false),Ship(4, {0, 6}, false),Ship(5, {0, 8}, false)};
        for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i),i+1);}
        //i
    }else
        for(int i=0;i<5;i++){
            do{
                if(bonnePosition==false)cout<<"Bateau au mauvais endroit"<<endl;
                do{
                    cout << "Position X (entre 0 et 9) bateau " << i+1 << " : ";
                    cin >> X;
                }while(X<0 || X>9);
                do{
                    cout << "Position Y (entre 0 et 9) bateau " << i+1 << " : ";
                    cin >> Y;
                }while(Y<0 || Y>9);
                cout << "Vertical (v) ou Horizontal (h) ";
                cin >> V;
                if(V=="v")VH=true;
                else VH=false;
                if(i==0 || i==1)bonnePosition=grid.placeShip(Ship(i+2,{X,Y},VH),i);
                else bonnePosition=grid.placeShip(Ship(i+1,{X,Y},VH),i);
            }while(bonnePosition==false);
        }
}

pair<int,int> Player::attack(IPlayer* player){
    int X,Y;
    string V;
    pair<int,int> result;
    bool bonnePosition=true;
    do{play.display();
        if(bonnePosition==false)cout<<"mauvais endroit"<<endl;
        do{
            cout << "Position X (entre 0 et 9) d'attaque " << " : ";
            cin >> X;
            cout << "Position Y (entre 0 et 9) d'attaque " << " : ";
            cin >> Y;
        }while(X>9 || X<0 || Y>9 || Y<0 || player->grid.grid[Y][X] == 'O' || player->grid.grid[Y][X] == 'X');
    }while(bonnePosition==false);
    if (player->isTouched({Y,X})){
            player->grid.vieShips[(player->grid.grid[Y][X]-'0')-1]-=1;
            player->grid.isSunk((player->grid.grid[Y][X]-'0')-1,play);
            player->grid.grid[Y][X] = 'X';
            this->play.grid[Y][X]='X';
            cout << "Touché !" << endl;
        }
        else {
            player->grid.grid[Y][X] = 'O';
            this->play.grid[Y][X]='O';
            cout << "Dans l'eau !" << endl;
        }
    result.first = X;
    result.second = Y;
    return result;
}

void Player::defense(Ship ship, pair<int,int> coordinates, IPlayer* player){
    vector<vector<int>> places;int X=coordinates.first;int Y=coordinates.second;
    if(X>0)places.push_back(vector<int>{X-1,Y});if(X<9)places.push_back(vector<int>{X+1,Y});if(Y>0)places.push_back(vector<int>{X,Y-1});if(Y<9)places.push_back(vector<int>{X,Y+1});
    random_shuffle(places.begin(),places.end());
    for(int i=0;i<4;i++){
        Ship shipTest=ship;
        shipTest.coordinates.first=places[i][0];shipTest.coordinates.second=places[i][1];
        if(grid.placeShip(ship,ship.numero)){
            player->play.grid[coordinates.first][coordinates.second]='X';
            break;
        }
    }
}

pair<int,int> Player::whatToDo(IPlayer* player,pair<int,int> coordinates){
    return this->attack(player);

}

bool Player::isTouched(pair<int,int>coordinates){
    if (grid.grid[coordinates.first][coordinates.second] != '~' || grid.grid[coordinates.first][coordinates.second] != 'O' || grid.grid[coordinates.first][coordinates.second] != 'X'){
        return true;
    }
    return false;
}
string Player::getName() const{
    return name;
}
int Player::getNbDefense(){
    return 1;
}
void Player::setName(string newName){
    name = newName;
}

void Player::getEnvironment(){
        grid.display();
}