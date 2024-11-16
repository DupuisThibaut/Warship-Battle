#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

#include "../Objects/Ship.h"
#include "../Objects/Grid.h"
#include "Iplayer.h"
//Classe player qui étend IPlayer et qui désigne un vrai joueur
using namespace std;
#ifndef PLAYER_H
#define PLAYER_H

class Player : public IPlayer{
    public:
        //Nom du joueur
        string name;
        //Constructeur de la classe Player
        Player(string name) : name(name) {}
        //Implémentation de la fonction de placement pour le joueur
        void placeShips() override{
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
        //Fonction qui choisit d'attaquer ou défendre
        pair<int,int> whatToDo(IPlayer* player,pair<int,int> coordinates) override {
            return attack(player);

        }
        //Implémentation de la fonction d'attaque pour le joueur
        pair<int,int> attack(IPlayer* player) override {
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
                    play.grid[Y][X]='X';
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
        void defense(Ship ship, pair<int,int> coordinates, IPlayer* player) override {
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
        //Implémentation de la détection de touché
        bool isTouched(pair<int,int>coordinates) override {
            if (grid.grid[coordinates.first][coordinates.second] != '~' || grid.grid[coordinates.first][coordinates.second] != 'O' || grid.grid[coordinates.first][coordinates.second] != 'X'){
                return true;
            }
            return false;
        }    
        //Implémentation du getteur de nom de joueur
        string getName() const override{
            return name;
        }    
        int getNbDefense() override {
            return 1;
        }    
        //Setteur pour le nom du joueur
        void setName(string newName) {
            name = newName;
        }    
        //Implémentation de la fonction pour obtenir la grille grid
        void getEnvironment() override {
                grid.display();
        }
};
#endif