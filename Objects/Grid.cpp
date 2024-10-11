#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Ship.cpp"

using namespace std;

class Grid {
public:
    vector<vector<char> > grid;
    vector<Ship> ships;
    vector<int> vieShips;

    Grid() : grid(10, vector<char>(10, '~')), vieShips(5, 0) {}

    bool placeShip(Ship ship, int numero) {
        pair<int, int> coordinates = ship.getCoordinates();
        bool isVertical = ship.getIsVertical();
        ship.placeShip(coordinates,isVertical);
        vector<int> X;
        vector<int> Y;
        if (isVertical){
            for (int i = 0; i < ship.getSize(); i++)
            {
                if(grid[(coordinates.second)+i][coordinates.first]=='S')return false;
                X.push_back((coordinates.second)+i);Y.push_back(coordinates.first);
            }
        }
        else {
        for (int i = 0; i < ship.getSize(); i++)
            {
                if(grid[coordinates.second][(coordinates.first)+i]=='S')return false;
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

    void display() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    void isSunk(int numero){
        if(vieShips[numero]==0){
            ships[numero].isSunk=true;
        }
    }

    bool allSunk(){
        // Commentaire cout
        //cout<< vieShips[0]<<endl;
        //cout<< vieShips[1]<<endl;
        //cout<< vieShips[2]<<endl;
        //cout<< vieShips[3]<<endl;
        //cout<< vieShips[4]<<endl;
        isSunk(0);isSunk(1);isSunk(2);isSunk(3);isSunk(4);
        for(int i=0;i<5;i++){
            if(ships.at(i).getSunk()==false)return false;
        }return true;
    }
};

