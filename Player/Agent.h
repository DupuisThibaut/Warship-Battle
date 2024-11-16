#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include "Iplayer.h"
#include "../Game.h"

using namespace std;
#ifndef AGENT_H
#define AGENT_H

using namespace std;

//Classe qui étend IPlayer et qui désigne l'agent (joueur non humain)
class Agent : public IPlayer{
    public :
        //Nom de l'agent
        string name;
        //Environnement dans lequel il se trouve
        Game* game;
        //Liste des prochains coups
        vector<int> coups;
        //Nombre de défenses restantes
        int nbdefense=1;
        //Constructeur pour la classe Agent
        Agent(string name) : name(name){for(int i=0;i<10;i++){
            if(i%2==0)for(int j=0;j<10;j++){if((i*10+j)%2!=0)coups.push_back(1);else coups.push_back(2);}
            else{for(int j=0;j<10;j++){if((i*10+j)%2!=0)coups.push_back(2);else coups.push_back(1);}}}

        }        
    //Actions :
        //Implémentation de la fonction de placement pour l'agent
        void placeShips() override {
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
        //Implémentation de la fonction d'attaque pour l'agent
        pair<int,int> attack(IPlayer* player) override{
            int X,Y;
            pair<int,int> result;
            vector<int> p=prochainCoup();X=p[0];Y=p[1];coups[X*10+Y]=0;
            if (player->isTouched({Y,X})){
                player->grid.vieShips[(player->grid.grid[Y][X]-'0')-1]-=1;
                player->grid.isSunk((player->grid.grid[Y][X]-'0')-1,play);
                if(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].isSunk==false){play.grid[Y][X]='X';changeCoups(X,Y,3);}
                else{
                    if (player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getIsVertical()) {
                        for (int i = 0; i < player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getSize(); i++){
                            play.grid[player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second+i][player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first] = ((player->grid.grid[Y][X]-'0')-1+1)+'0';
                            changeCoups(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first,player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second+i,1);
                        }
                    }
                    else{
                        for (int i = 0; i < player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getSize(); i++){
                            play.grid[player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second][player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first+i] = ((player->grid.grid[Y][X]-'0')-1+1)+'0';
                            changeCoups(player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().first+i,player->grid.ships[(player->grid.grid[Y][X]-'0')-1].getCoordinates().second,1);
                        }
                    }
                }
                player->grid.grid[Y][X] = 'X';
                cout << "Touché !" << endl;
            }
            else {
                player->grid.grid[Y][X] = 'O';
                play.grid[Y][X]='O';
                cout << "Dans l'eau !" << endl;
            }
            result.first = X;
            result.second = Y;
            return result;
        }
        //Implémentation de la fonction pour récuperer le prochain coup pour l'agent
        vector<int> prochainCoup(){
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
        void changeCoups(int X, int Y, int valeur){
            if(X>0 && coups[(X-1)*10+Y]>0)coups[(X-1)*10+Y]=valeur;
            if(X<9 && coups[(X+1)*10+Y]>0)coups[(X+1)*10+Y]=valeur;
            if(Y>0 && coups[X*10+Y-1]>0)coups[X*10+Y-1]=valeur;
            if(Y<9 && coups[X*10+Y+1]>0)coups[X*10+Y+1]=valeur;
            if(valeur>1)ameliorerCoups(Y,X);
        }
        void ameliorerCoups(int X, int Y){
            if(X-1>=0){if(play.grid[X-1][Y]=='X'){if(X<9)if(play.grid[X+1][Y]=='~'){coups[(Y)*10+X+1]+=1;}if(X-2>=0)if(play.grid[X-2][Y]=='~')coups[(Y)*10+X-2]+=1;}}
            if(X+1<=9){if(play.grid[X+1][Y]=='X'){if(X>0)if(play.grid[X-1][Y]=='~'){coups[(Y)*10+X-1]+=1;}if(X+2<=9)if(play.grid[X+2][Y]=='~')coups[(Y)*10+X+2]+=1;}}
            if(Y-1>=0){if(play.grid[X][Y-1]=='X'){if(Y<9)if(play.grid[X][Y+1]=='~'){coups[(Y+1)*10+X]+=1;}if(Y-2>=0)if(play.grid[X][Y-2]=='~')coups[(Y-2)*10+X]+=1;}}
            if(Y+1<=9){if(play.grid[X][Y+1]=='X'){if(Y>0)if(play.grid[X][Y-1]=='~'){coups[(Y-1)*10+X]+=1;}if(Y+2<=9)if(play.grid[X][Y+2]=='~')coups[(Y+2)*10+X]+=1;}}
        }
        //Implémentation de la fonction de défense 
        vector<int> chooseDefAt(){
            vector<char> sunked = {'X', 'O', '~','e'};
            vector<int> result;
            vector<char> sunk = {'X', 'O', '~','e'};
            int cpt_sunked = 0;
            int cpt_sunk = 5;
            for(int i = 0; i<10;i++){
                for(int j = 0;j<10;j++){
                    if(find(sunked.begin(),sunked.end(),play.grid[i][j])==sunked.end()){
                            sunked.insert(sunked.begin(), play.grid[i][j]);
                            cpt_sunked++;
                    }
                    if(find(sunk.begin(),sunk.end(),grid.grid[i][j])==sunk.end()){
                            sunk.insert(sunk.begin(), grid.grid[i][j]);
                            cpt_sunk--;
                    }
                }
            }
            cout<<"sunked : "<<cpt_sunked<<" sunk : "<<cpt_sunk<<endl;
            int ratio;
            if(cpt_sunk==0){ratio=1;}
            else {ratio = floor(cpt_sunked / cpt_sunk);}
            result.push_back(ratio);result.push_back(cpt_sunked);result.push_back(cpt_sunk);
            return result;
        }
        //Fonction qui choisit d'attaquer ou défendre
        pair<int,int> whatToDo(IPlayer* player,pair<int,int> coordinates) override {
            cout<<"Défenses restantes : "<<nbdefense<<endl;
            vector<int> datas = chooseDefAt();
            pair<int,int> result;
            int numero = 100;
            bool test = isItTheBiggestBoat(coordinates, numero);
            cout<<"ratio : "<<datas[0]<<" coordonnées :"<<(coordinates.first<10 && coordinates.second<10)<<" Biggestboat :"<<test<<" nbdefense : "<<(nbdefense==1)<<endl;
            if(((datas[0]<1 && datas[2]>=2) || datas[2]>=4 ) && (coordinates.first<10 && coordinates.second<10) && nbdefense==1 && test){
                cout<<"Debug test :"<<(((datas[0]<1 && nbdefense==1 && datas[2]>2 && test) || datas[2]>=4 ) && (coordinates.first<10 && coordinates.second<10))<<endl;
                pair<int,int> coor;coor.first=coordinates.second;coor.second=coordinates.first;
                defense(grid.ships[numero-1],coor,player);
                cout<<"Je défends sur :"<<coordinates.first<<","<<coordinates.second<<endl;
                nbdefense=0;
                grid.display();
                result = make_pair(10,10);
            }
            else{
                result = attack(player);
            }
            return result;
        }

        //Fonction de défense de l'agent
        void defense(Ship ship, pair<int,int> coordinates, IPlayer* player){
            vector<vector<int>> places;int X=ship.coordinates.second;int Y=ship.coordinates.first;
            if(X>0)places.push_back(vector<int>{X-1,Y});if(X<9)places.push_back(vector<int>{X+1,Y});if(Y>0)places.push_back(vector<int>{X,Y-1});if(Y<9)places.push_back(vector<int>{X,Y+1});
            random_shuffle(places.begin(),places.end());
            bool test=false;
            cout<<"X "<<X<<endl;
            cout<<"Y "<<Y<<endl;
            cout<<"places "<<places.size()<<endl;
            for(int i=0;i<places.size();i++){
                if(test==false){
                    Ship shipTest=ship;
                    shipTest.coordinates.first=places[i][0];shipTest.coordinates.second=places[i][1];
                    if(grid.placeShip(ship,ship.numero)){
                        player->play.grid[coordinates.first][coordinates.second]='X';
                        test=true;
                    }
                }
            }
            cout<<"test"<<test<<endl;
            if(test){
                pair<int, int> coordinatesShip = ship.getCoordinates();
                bool isVertical = ship.getIsVertical();
                bool placement;
                vector<int> X;
                vector<int> Y;
                for(int i=0;i<places.size();i++){
                    placement=true;
                    if (isVertical){
                        for (int i = 0; i < ship.getSize(); i++)
                        {
                            if(coordinates.second+i>9)placement=false;
                            if(placement){
                                if(grid.grid[(coordinates.second)+i][coordinates.first]!='~' && grid.grid[(coordinates.second)+i][coordinates.first]!='O')placement=false;
                            }
                            if(placement){
                                X.push_back((coordinates.second)+i);Y.push_back(coordinates.first);
                            }
                        }
                    }
                    else {
                        for (int i = 0; i < ship.getSize(); i++)
                        {
                            if(coordinates.first+i>9)placement=false;
                            if(placement){
                                if(grid.grid[coordinates.second][(coordinates.first)+i]!='~' && grid.grid[coordinates.second][(coordinates.first)+i]!='O')placement=false;
                            }
                            if(placement){
                                X.push_back((coordinates.second));Y.push_back(coordinates.first+i);
                            }
                        }
                    }
                }
                for(int i=0;i<X.size();i++){
                    player->grid.grid[X[i]][Y[i]]='~';
                }
            }
        }
    //Lecture :
        //Implémentation des getteurs
        void getEnvironment() override{
            grid.display();
        }
        string getName() const override {
            return name;
        }
        int getNbDefense() override{
            return nbdefense;
        }
        //Implémentation de la détection de touché
        bool isTouched(pair<int,int>coordinates) override {
            if (grid.grid[coordinates.first][coordinates.second] == '~')return false;
            if (grid.grid[coordinates.first][coordinates.second] == 'O')return false;
            if (grid.grid[coordinates.first][coordinates.second] == 'X')return false;
            return true;
        }
        //Fonction pour savoir si le bateau aux coordonnées X et Y est le plus grand
        bool isItTheBiggestBoat(pair<int,int>coordinates, int &num_boat){
            if(coordinates.first<10 && coordinates.second<10){
                if(grid.grid[coordinates.second][coordinates.first]=='~' || grid.grid[coordinates.second][coordinates.first]=='O') {return false;}
                cout<<"debug ping"<<endl;
                for(size_t i=0;i<grid.ships.size();i++){
                    for(size_t j =0;j<grid.ships[i].getSize();j++){
                        if(grid.ships[i].getIsVertical()==true){
                            if((grid.ships[i].coordinates.second)+j == coordinates.second && grid.ships[i].coordinates.first == coordinates.first){num_boat = i;}
                        }
                        else{
                            if((grid.ships[i].coordinates.first)+j == coordinates.first && grid.ships[i].coordinates.second == coordinates.second){num_boat = i;}
                        }
                    }
                }
                cout<<"num_boat : "<<num_boat<<endl;
                if(num_boat == 100 || grid.vieShips[num_boat]!=(grid.ships[num_boat].getSize()-1)) return false;
                for(int i=num_boat+1;i<5;i++){
                    if(grid.vieShips[i]!=0){return false;}
                }
                return true;
            }
            return false;
        }
};
#endif