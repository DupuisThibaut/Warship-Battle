#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sys/types.h>
#include <unistd.h>
//#include "Objects/Ship.cpp"
#include "Agent.h"
#include "../Objects/Grid.h"
#include "../Game.h"

using namespace std;

Agent::Agent(string name) : name(name){for(int i=0;i<10;i++){
    if(i%2==0)for(int j=0;j<10;j++){if((i*10+j)%2!=0)coups.push_back(1);else coups.push_back(2);}
    else{for(int j=0;j<10;j++){if((i*10+j)%2!=0)coups.push_back(2);else coups.push_back(1);}}}

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

pair<int,int> Agent::attack(IPlayer* player){
    int X,Y;
    pair<int,int> result;
    vector<int> p=prochainCoup();X=p[0];Y=p[1];coups[X*10+Y]=0;
    if (player->isTouched({Y,X})){
        player->grid.vieShips[(player->grid.grid[Y][X]-'0')-1]-=1;
        player->grid.isSunk((player->grid.grid[Y][X]-'0')-1,this->play);
        if(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].isSunk==false){this->play.grid[Y][X]='X';changeCoups(X,Y,3);}
        else{
            if (player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getIsVertical()) {
                for (int i = 0; i < player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getSize(); i++){
                    this->play.grid[player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second+i][player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first] = ((player->grid.grid[Y][X]-'0')-1+1)+'0';
                    changeCoups(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first,player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second+i,1);
                }
            }
            else{
                for (int i = 0; i < player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getSize(); i++){
                    this->play.grid[player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second][player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first+i] = ((player->grid.grid[Y][X]-'0')-1+1)+'0';
                    changeCoups(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first+i,player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second,1);
                }
            }
        }
        player->grid.grid[Y][X] = 'X';
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

void Agent::changeCoups(int X, int Y, int valeur){
        if(X>0 && coups[(X-1)*10+Y]>0)coups[(X-1)*10+Y]=valeur;
        if(X<9 && coups[(X+1)*10+Y]>0)coups[(X+1)*10+Y]=valeur;
        if(Y>0 && coups[X*10+Y-1]>0)coups[X*10+Y-1]=valeur;
        if(Y<9 && coups[X*10+Y+1]>0)coups[X*10+Y+1]=valeur;
        if(valeur>1)ameliorerCoups(Y,X);
}

void Agent::ameliorerCoups(int X, int Y){
    if(X-1>=0){if(this->play.grid[X-1][Y]=='X'){if(X<9)if(this->play.grid[X+1][Y]=='~'){coups[(Y)*10+X+1]+=1;}if(X-2>=0)if(this->play.grid[X-2][Y]=='~')coups[(Y)*10+X-2]+=1;}}
    if(X+1<=9){if(this->play.grid[X+1][Y]=='X'){if(X>0)if(this->play.grid[X-1][Y]=='~'){coups[(Y)*10+X-1]+=1;}if(X+2<=9)if(this->play.grid[X+2][Y]=='~')coups[(Y)*10+X+2]+=1;}}
    if(Y-1>=0){if(this->play.grid[X][Y-1]=='X'){if(Y<9)if(this->play.grid[X][Y+1]=='~'){coups[(Y+1)*10+X]+=1;}if(Y-2>=0)if(this->play.grid[X][Y-2]=='~')coups[(Y-2)*10+X]+=1;}}
    if(Y+1<=9){if(this->play.grid[X][Y+1]=='X'){if(Y>0)if(this->play.grid[X][Y-1]=='~'){coups[(Y-1)*10+X]+=1;}if(Y+2<=9)if(this->play.grid[X][Y+2]=='~')coups[(Y+2)*10+X]+=1;}}
}
vector<int> Agent::prochainCoup(){
    int m=0;vector<vector<int>> liste;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(coups[i*10+j]>m){liste.clear();liste.push_back(vector<int>({i,j}));m=coups[i*10+j];}
            if(coups[i*10+j]==m)liste.push_back(vector<int>({i,j}));
        }
    }
    int x=rand()%liste.size();cout << "x" << x << endl;cout << "liste" << liste.size() << endl;cout << "coups" << coups.size() << endl;
    cout << "X LISTE " << liste[x][0] << " " << liste[x][1] << endl;
    return liste[x];
}

vector<int> Agent::chooseDefAt(){
    vector<char> sunked;
    vector<int> result;
    sunked.push_back('X');sunked.push_back('O');sunked.push_back('~');
    vector<int> sunk;
    sunk.push_back('X');sunk.push_back('O');sunk.push_back('~');
    float cpt_sunked = 0;
    float cpt_sunk = 0;
    for(int i = 0; i<10;i++){
        for(int j = 0;j<10;j++){
            if(find(sunked.begin(),sunked.end(),this->play.grid[j][i]) != sunked.end()){
                cpt_sunked++;
            }
            if(find(sunk.begin(),sunk.end(),this->grid.grid[j][i]) != sunk.end()){
                cpt_sunk++;
            }
        }
    }
    int ratio;
    if(cpt_sunk==0){ratio=1;}
    else {ratio = int(cpt_sunked / cpt_sunk);} 
    cout<<"sunked/sunk : "<<ratio<<endl;
    result.push_back(ratio);result.push_back(cpt_sunked);result.push_back(cpt_sunk);
                
    return result;

}

void Agent::defense(pair<int,int> coordinates){
}

pair<int,int> Agent::whatToDo(IPlayer* player,pair<int,int> coordinates){
    cout<<"Défenses restantes : "<<this->nbdefense<<endl;
    vector<int> datas = chooseDefAt();
    pair<int,int> result;
    if(datas[0]<1 && this->nbdefense==1 && datas[2]>2 && coordinates.first<10 && isItTheBiggestBoat(coordinates,datas)){
        this->defense(coordinates);
        this->nbdefense =0;
        cout<<"Je défends sur :"<<coordinates.first<<","<<coordinates.second<<endl;
        result = make_pair(10,10);
    }
    else{
        result = this->attack(player);
    }
    return result;
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

bool Agent::isItTheBiggestBoat(pair<int,int>coordinates,vector<int> datas){
    if(grid.grid[coordinates.second][coordinates.first]=='~') return false;
    if(grid.grid[coordinates.second][coordinates.first]=='O') return false;
    int num_boat = 0;
    for(size_t i=0;i<grid.ships.size();i++){
        for(size_t j =0;j<grid.ships[i].size;j++){
            if(grid.ships[i].getIsVertical()==true){
                if(grid.ships[i].coordinates.second+j == coordinates.first && grid.ships[i].coordinates.first == coordinates.second){
                    num_boat = grid.ships[i].size;
                }
            }
            else{
                if(grid.ships[i].coordinates.first+j == coordinates.second && grid.ships[i].coordinates.second == coordinates.first){
                    num_boat = grid.ships[i].size;
                }
            }
        }
    }
    if(num_boat == 0){return false;}
    if(num_boat==5){return true;}
    if(num_boat==1 && datas[2]<4){return false;}
    for(int i=2;i<5;i++){
        if(i>num_boat && grid.vieShips[i]!=0){
            return false;

        }
    }
    return true;
}