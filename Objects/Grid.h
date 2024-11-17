#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Ship.h"
//Cette classe modélise la grille sur laquelle le joueur place/attaque
using namespace std;
#ifndef GRID_H
#define GRID_H
class Grid {
public:
    //Liste modélisant le plateau de jeu
    vector<vector<char> > grid;
    //Liste des bateaux disponibles
    vector<Ship> ships;
    //Liste stockant le nombre de vies des bateaux
    vector<int> vieShips;
    //Constructeur de la classe Grid
    Grid() : grid(10, vector<char>(10, '~')), vieShips(5, 0) {}
    //Fonction pour placer un bateau
    bool placeShip(Ship ship, int numero) {
        pair<int, int> coordinates = ship.getCoordinates();
        bool isVertical = ship.getIsVertical();
        ship.placeShip(coordinates,isVertical);
        vector<int> X;
        vector<int> Y;
        if (isVertical){
            for (int i = 0; i < ship.getSize(); i++)
            {
                cout<<"k"<<endl;
                if(coordinates.second+i>9)return false;
                cout<<"l"<<endl;
                if(vieShips[numero-1]!=0){
                    cout<<"m"<<endl;
                    if(grid[(coordinates.second)+i][coordinates.first]!='~' && grid[(coordinates.second)+i][coordinates.first]!='O')return false;
                }
                else{
                    if(grid[(coordinates.second)+i][coordinates.first]!='~')return false;
                } 
                X.push_back((coordinates.second)+i);Y.push_back(coordinates.first);
            }
        }
        else {
        for (int i = 0; i < ship.getSize(); i++)
            {
                cout<<"k"<<endl;
                if(coordinates.first+i>9)return false;
                cout<<"l"<<endl;
                if(vieShips[numero-1]!=0){
                    cout<<"m"<<endl;
                    if(grid[coordinates.second][(coordinates.first)+i]!='~' && grid[coordinates.second][(coordinates.first)+i]!='O')return false;
                }
                else{
                    if(grid[coordinates.second][(coordinates.first)+i]!='~')return false;
                }
                X.push_back((coordinates.second));Y.push_back(coordinates.first+i);
            }
        }
        if(vieShips[numero-1]==0){
            for (int i = 0; i < ship.getSize(); i++){
                grid[X[i]][Y[i]] = numero+'0';
            }
            ship.numero=numero;
            ships.push_back(ship);
            vieShips[numero-1]=ship.getSize();
        }else{
            for(int i=0;i<ship.getSize();i++){
                if(isVertical){
                    grid[ships[numero].getCoordinates().first+i][ships[numero].getCoordinates().second]='~';
                }else{
                    grid[ships[numero].getCoordinates().first][ships[numero].getCoordinates().second+i]='~';
                }
            }
            for(int i=0;i<ship.getSize();i++){
                if(isVertical){
                    grid[X[i]][Y[i]]=numero+'0';
                }else{
                    grid[X[i]][Y[i]]=numero+'0';
                }
            }
            ships[numero]=ship;
        }
        return true;
    }
    //Fonction d'affichage de la grille
    void display() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    //Fonction qui met à jour "vieShips" en fonction de l'état d'un bateau
    void isSunk(int numero, Grid grille){
        if(vieShips[numero]==0){
            ships[numero].isSunk=true;
        }
    }
    //Fonction qui renvoie si la partie est terminée (tout les bateaux ont coulé) ou non
    bool allSunk(){
        for(int i=0;i<5;i++){
            if(ships.at(i).getSunk()==false)return false;
        }
        return true;
    }
};
#endif