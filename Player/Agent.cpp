#include <iostream>
#include <vector>
#include <string>
#include <random>

//#include "Objects/Ship.cpp"
#include "Objects/Grid.cpp"
#include "Player/IPlayer.cpp"
#include "Player/Player.cpp"
#include "Game.cpp"

using namespace std;



class Agent : public IPlayer{
    public :
        string name;
        Game* game;

        Agent(string name) : name(name){}

        void placeShips(){
            vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {0, 2}, false),Ship(3, {0, 4}, false),Ship(4, {0, 6}, false),Ship(5, {0, 8}, false)};
            for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i),i+1);}
        }

        void attack(IPlayer* player){
            int X,Y;
            X=rand()%10;Y=rand()%10;
            do{
                X=rand()%10;Y=rand()%10;
            }while(player->grid.grid[Y][X] == 'O' || player->grid.grid[Y][X] == 'X');
            if (player->isTouched({Y,X})){
                player->grid.vieShips[(player->grid.grid[Y][X]-'0')-1]-=1;
                player->grid.isSunk((player->grid.grid[Y][X]-'0')-1);
                player->grid.grid[Y][X] = 'X';
                this->play.grid[Y][X]='X';
                cout << "Touché !" << endl;
            }
            else {
                player->grid.grid[Y][X] = 'O';
                this->play.grid[Y][X]='O';
                cout << "Dans l'eau !" << endl;
            }
        }

        void getEnvironment(){
            grid.display();
        }
        string getName() const override{
            return name;
        }
        bool isTouched(pair<int,int>coordinates){
            if (grid.grid[coordinates.first][coordinates.second] == '~')return false;
            if (grid.grid[coordinates.first][coordinates.second] == 'O')return false;
            if (grid.grid[coordinates.first][coordinates.second] == 'X')return false;
            return true;
        }
};