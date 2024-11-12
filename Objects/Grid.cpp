#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Ship.h"
#include "Grid.h"
using namespace std;

Grid::Grid() : grid(10, vector<char>(10, '~')), vieShips(5, 0) {}

bool Grid::placeShip(Ship ship, int numero) {
    pair<int, int> coordinates = ship.getCoordinates();
    bool isVertical = ship.getIsVertical();
    ship.placeShip(coordinates,isVertical);
    vector<int> X;
    vector<int> Y;
    if (isVertical){
        for (int i = 0; i < ship.getSize(); i++)
        {
            if(coordinates.second+i>9)return false;
            if(grid[(coordinates.second)+i][coordinates.first]!='~')return false;
            X.push_back((coordinates.second)+i);Y.push_back(coordinates.first);
        }
    }
    else {
    for (int i = 0; i < ship.getSize(); i++)
        {
            if(coordinates.first+i>9)return false;
            if(grid[coordinates.second][(coordinates.first)+i]!='~')return false;
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
                grid[ships[numero].getCoordinates().first+i][ships[numero].getCoordinates().second]='O';
            }else{
                grid[ships[numero].getCoordinates().first][ships[numero].getCoordinates().second+i]='O';
            }
        }
        for(int i=0;i<ship.getSize();i++){
            if(isVertical){
                grid[(coordinates.second)+i][coordinates.first]=numero+'0';
            }else{
                grid[coordinates.second][coordinates.first+i]=numero+'0';
            }
        }
        ships[numero]=ship;
    }
    return true;
}

void Grid::display() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void Grid::isSunk(int numero, Grid grille){
    if(vieShips[numero]==0){
        cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"<<numero<<endl;
        cout<<ships[numero].getSize()<<endl;
        ships[numero].isSunk=true;
    }
}

bool Grid::allSunk(){
    for(int i=0;i<5;i++){
        if(ships.at(i).getSunk()==false)return false;
    }return true;
}
