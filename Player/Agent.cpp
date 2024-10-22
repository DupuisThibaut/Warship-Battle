#include <iostream>
#include <vector>
#include <string>
#include <random>

//#include "Objects/Ship.cpp"
#include "Agent.h"
#include "../Objects/Grid.h"
#include "../Game.h"

using namespace std;

Agent::Agent(string name) : name(name){for(int i=0;i<10;i++){for(int j=0;j<10;j++){if((i*10+j)%2!=0)coups.push_back(1);else coups.push_back(2);}}
}

void Agent::placeShips(){
    srand(getpid()+(rand()%100));
    bool bonnePosition=true;
    for (int i = 0; i < 5; i++){
        do{
            int X=rand()%10,Y=rand()%10,V=rand()%2;bool VH;
            if(V==1)VH=true;
            else VH=false;
            if(i==0 || i==1)bonnePosition=grid.placeShip(Ship(i+2,{X,Y},VH),i+1);
            else bonnePosition=grid.placeShip(Ship(i+1,{X,Y},VH),i+1);
        }while(bonnePosition==false);
    }
    cout<<"Bateau placé"<<endl;
    grid.display();
}

void Agent::attack(IPlayer* player){
    int X,Y;
    // srand(getpid()+(rand()%100));
    // X=rand()%10;Y=rand()%10;
    // do{
    //     X=rand()%10;Y=rand()%10;
    // }while(player->grid.grid[Y][X] == 'O' || player->grid.grid[Y][X] == 'X');
    vector<int> p=prochainCoup();X=p[0];Y=p[1];coups[X*10+Y]=0;
    if (player->isTouched({Y,X})){
        player->grid.vieShips[(player->grid.grid[Y][X]-'0')-1]-=1;
        cout<<"JJJJJJJJJJJJJJJJJJJJJJJ"<<(player->grid.grid[Y][X]-'0')-1<<endl;
        player->grid.isSunk((player->grid.grid[Y][X]-'0')-1,play);
        if(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].isSunk==false)
        this->play.grid[Y][X]='X';
        player->grid.grid[Y][X] = 'X';
        if(X>0 && coups[(X-1)*10+Y]>0)coups[(X-1)*10+Y]+=2;
        if(X<9 && coups[(X+1)*10+Y]>0)coups[(X+1)*10+Y]+=2;
        if(Y>0 && coups[X*10+Y-1]>0)coups[X*10+Y-1]+=2;
        if(Y<9 && coups[X*10+Y+1]>0)coups[X*10+Y+1]+=2;
        cout << "Touché !" << endl;
    }
    else {
        player->grid.grid[Y][X] = 'O';
        this->play.grid[Y][X]='O';
        cout << "Dans l'eau !" << endl;
    }
}

vector<int> Agent::prochainCoup(){
    int m=0;vector<vector<int>> liste;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(coups[i*10+j]>m){liste.clear();liste.push_back(vector<int>({i,j}));m=coups[i*10+j];cout<<"m"<<m<<endl;}
            if(coups[i*10+j]==m)liste.push_back(vector<int>({i,j}));
        }
    }
    int x=rand()%liste.size();cout << "x" << x << endl;cout << "liste" << liste.size() << endl;cout << "coups" << coups.size() << endl;
    cout << "X LISTE " << liste[x][0] << " " << liste[x][1] << endl;
    return liste[x];
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