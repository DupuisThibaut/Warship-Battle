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
    for (int i = 0; i < ship.getSize(); i++){
        grid[X[i]][Y[i]] = numero+'0';
    }
    ships.push_back(ship);
    vieShips[numero-1]=ship.getSize();
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
        if (ships[numero].getIsVertical()) {
            for (int i = 0; i < ships[numero].getSize(); i++){
                cout<<"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK"<<endl;
                grille.grid[ships[numero].getCoordinates().second+i][ships[numero].getCoordinates().first] = (numero+1)+'0';
            }
        }
        else{
            for (int i = 0; i < ships[numero].getSize(); i++){
                cout<<"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<grille.grid[ships[numero].getCoordinates().second][ships[numero].getCoordinates().first+i]<<endl;
                grille.grid[ships[numero].getCoordinates().second][ships[numero].getCoordinates().first+i] = (numero+1)+'0';
                cout<<grille.grid[ships[numero].getCoordinates().second][ships[numero].getCoordinates().first+i]<<endl;
            }
        }
    }
}

bool Grid::allSunk(){
    // Commentaire cout
    //cout<< vieShips[0]<<endl;
    //cout<< vieShips[1]<<endl;
    //cout<< vieShips[2]<<endl;
    //cout<< vieShips[3]<<endl;
    //cout<< vieShips[4]<<endl;
    for(int i=0;i<5;i++){
        if(ships.at(i).getSunk()==false)return false;
    }return true;
}

