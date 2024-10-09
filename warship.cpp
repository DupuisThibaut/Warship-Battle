#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Classe Ship représentant un bateau
class Ship {
public:
    int size;
    bool isSunk;
    pair<int, int> coordinates;
    bool isVertical;

    Ship(int size, pair<int, int> coordinates, bool isVertical) : size(size), coordinates(coordinates), isVertical(isVertical), isSunk(false) {}

    void placeShip(pair<int, int> coords, bool isVertical) { 
        coordinates = coords;
        this->isVertical = isVertical;
    }

    int getSize() { return size; }

    bool getIsVertical() { return isVertical; }

    pair<int, int> getCoordinates() { return coordinates; }
};

class Grid {
public:
    vector<vector<char> > grid;
    vector<Ship> ships;

    Grid() : grid(10, vector<char>(10, '~')) {}

    void placeShip(Ship& ship) { 
        pair<int, int> coordinates = ship.getCoordinates();
        bool isVertical = ship.getIsVertical();
        ship.placeShip(coordinates,isVertical);
        if (isVertical){
            for (int i = 0; i < ship.getSize(); i++)
            {
                grid[(coordinates.first)+i][coordinates.second] = 'S'; 
            }
        }
        else {
        for (int i = 0; i < ship.getSize(); i++)
            {
                grid[coordinates.first][(coordinates.second)+i] = 'S'; 
            }
        }
        ships.push_back(ship);
    }

    void display() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};


class Player {
public:
    string name;
    Grid grid;

    Player(string name) : name(name) {}

    void placeShips(vector<Ship> ships) {        
        for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i));}
    }

    void attack(Player& player, pair<int,int> coordinates){
        if (player.grid.grid[coordinates.first][coordinates.second] == 'S'){
            player.grid.grid[coordinates.first][coordinates.second] = 'X';
            cout << "Touché !" << endl;
        }
        else {
            player.grid.grid[coordinates.first][coordinates.second] = 'O';
            cout << "Dans l'eau !" << endl;
        }
    }
};

class Game {
public:
    Player player1;
    Player player2;

    Game(string name1, string name2) : player1(name1), player2(name2) {}

    void start() {
        cout << "Placement des bateaux pour " << player1.name << endl;
        vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {2, 0}, false),Ship(3, {4, 0}, false),Ship(4, {6, 0}, false),Ship(5, {8, 0}, false)};
        player1.placeShips(ships);
        cout << "Placement des bateaux pour " << player2.name << endl;
        player2.placeShips(ships);
    }
};

int main() {
    Game game("Joueur 1", "Joueur 2");
    game.start();
    game.player1.grid.display();
    game.player1.attack(game.player2, {0, 0});
    game.player2.grid.display();

    return 0;
}