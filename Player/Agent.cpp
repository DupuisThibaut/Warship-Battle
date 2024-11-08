#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <unistd.h>
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
        player->grid.isSunk((player->grid.grid[Y][X]-'0')-1,this->play);
        if(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].isSunk==false)this->play.grid[Y][X]='X';
        else{
            if (player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getIsVertical()) {
                for (int i = 0; i < player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getSize(); i++){
                    this->play.grid[player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second+i][player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first] = ((player->grid.grid[Y][X]-'0')-1+1)+'0';
                    if(X>0 && coups[(X-1)*10+Y]>0)coups[(X-1)*10+Y]-=3;
                    if(X<9 && coups[(X+1)*10+Y]>0)coups[(X+1)*10+Y]-=3;
                    if(Y>0 && coups[X*10+Y-1]>0)coups[X*10+Y-1]-=3;
                    if(Y<9 && coups[X*10+Y+1]>0)coups[X*10+Y+1]-=3;
                }
            }
            else{
                for (int i = 0; i < player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getSize(); i++){
                    this->play.grid[player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second][player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first+i] = ((player->grid.grid[Y][X]-'0')-1+1)+'0';
                    if(X>0 && coups[(X-1)*10+Y]>0)coups[(X-1)*10+Y]-=3;
                    if(X<9 && coups[(X+1)*10+Y]>0)coups[(X+1)*10+Y]-=3;
                    if(Y>0 && coups[X*10+Y-1]>0)coups[X*10+Y-1]-=3;
                    if(Y<9 && coups[X*10+Y+1]>0)coups[X*10+Y+1]-=3;
                }
            }
        }
        player->grid.grid[Y][X] = 'X';
        if(X>0 && coups[(X-1)*10+Y]>0){coups[(X-1)*10+Y]+=3;}
        if(X<9 && coups[(X+1)*10+Y]>0)coups[(X+1)*10+Y]+=3;
        if(Y>0 && coups[X*10+Y-1]>0)coups[X*10+Y-1]+=3;
        if(Y<9 && coups[X*10+Y+1]>0)coups[X*10+Y+1]+=3;
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
            if(coups[i*10+j]>m){liste.clear();liste.push_back(vector<int>({i,j}));m=coups[i*10+j];}
            if(coups[i*10+j]==m)liste.push_back(vector<int>({i,j}));
        }
    }
    int x=rand()%liste.size();
    return liste[x];
}

int Agent::chooseDefAt(){
    vector<char> sunked;
    sunked.push_back('X');sunked.push_back('O');sunked.push_back('~');
    vector<int> sunk;
    sunk.push_back('X');sunk.push_back('O');sunk.push_back('~');
    int cpt_sunked = 0;
    int cpt_sunk = 0;
    for(int i = 0; i<10;i++){
        for(int j = 0;i<10;i++){
            if(find(sunked.begin(),sunked.end(),this->play.grid[j][i]) != sunked.end()){
                sunked.push_back(this->play.grid[j][i]);
                cpt_sunked++;
            }
            if(find(sunk.begin(),sunk.end(),this->grid.grid[j][i]) != sunk.end()){
                sunk.push_back(this->grid.grid[j][i]);
                cpt_sunk++;
            }
        }
    }
    cout<<"sunked/sunk : "<<cpt_sunked/cpt_sunk<<endl;
    return int(cpt_sunked/cpt_sunk);

}

void Agent::defense(){
}

void Agent::whatToDo(IPlayer* player){
    cout<<"Défenses restantes : "<<this->nbdefense<<endl;
    if(this->chooseDefAt()<1 && this->nbdefense==1){
        this->defense();
        this->nbdefense =0;
        cout<<"Je défends"<<endl;
    }
    else{
        this->attack(player);
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