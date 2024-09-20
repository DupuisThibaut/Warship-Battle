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

    Ship(int size) : size(size), isSunk(false) {}

    void placeShip(pair<int, int> coords, bool isVertical) { 
        coordinates = coords;
        isVertical = isVertical;
    }
};

class Grid {
public:
    vector<vector<char> > grid;
    vector<Ship> ships;

    Grid() : grid(10, vector<char>(10, '~')) {}

    void placeShip(Ship& ship, pair<int, int> coordinates, bool isVertical) { 
        ship.placeShip(coordinates,isVertical);
        if (isVertical){        
            grid[coordinates.first][coordinates.second] = 'S'; 
        }
        else grid[coordinates.first][coordinates.second] = 'S'; 
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

    void placeShips() {
        // Placer les 5 bateaux : taille 2, 3, 3, 4, 5
        vector<pair<int, int> > coords;

        // Bateau de taille 2
        Ship ship2(2);
        coords = {{0, 0}, {0, 1}};
        grid.placeShip(ship2, coords);

        // Bateau de taille 3
        Ship ship3_1(3);
        coords = {{2, 0}, {2, 1}, {2, 2}};
        grid.placeShip(ship3_1, coords);

        // Autre bateau de taille 3
        Ship ship3_2(3);
        coords = {{4, 0}, {4, 1}, {4, 2}};
        grid.placeShip(ship3_2, coords);

        // Bateau de taille 4
        Ship ship4(4);
        coords = {{6, 0}, {6, 1}, {6, 2}, {6, 3}};
        grid.placeShip(ship4, coords);

        // Bateau de taille 5
        Ship ship5(5);
        coords = {{8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}};
        grid.placeShip(ship5, coords);
    }
};

class Game {
public:
    Player player1;
    Player player2;

    Game(string name1, string name2) : player1(name1), player2(name2) {}

    void start() {
        cout << "Placement des bateaux pour " << player1.name << endl;
        player1.placeShips();
        cout << "Placement des bateaux pour " << player2.name << endl;
        player2.placeShips();
    }
};

int main() {
    Game game("Joueur 1", "Joueur 2");
    game.start();
    game.player1.grid.display();

    return 0;
}