#include <iostream>
#include <vector>
#include <string>
#include <random>

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
class IPlayer{
    public:
        virtual void placeShips(vector<Ship> ships)=0;
        virtual void attack(IPlayer& opponent, pair<int,int> coordinates) = 0;
        virtual string getName() const = 0;
        virtual ~IPlayer(){}
};

class Player : public IPlayer{
public:
    string name;
    Grid grid;
    Grid play;

    Player(string name) : name(name) {}

    void placeShips(vector<Ship> ships) {        
        for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i));}
    }

    void attack(Player& player, pair<int,int> coordinates){
        if (player.isTouched(coordinates)){
            player.grid.grid[coordinates.first][coordinates.second] = 'X';
            cout << "Touché !" << endl;
        }
        else {
            player.grid.grid[coordinates.first][coordinates.second] = 'O';
            cout << "Dans l'eau !" << endl;
        }
    }

    bool isTouched(pair<int,int>coordinates){
        if (grid.grid[coordinates.first][coordinates.second] == 'S'){
            return true;
        }
        return false;
    }
    string getName() const override {
        return name;
    }
};



class Game {
public:
    IPlayer* player1;
    IPlayer* player2;

    Game(IPlayer* p1, IPlayer* p2) : player1(p1), player2(p2) {}

    void start() {
        cout << "Placement des bateaux pour " << player1->getName() << endl;
        vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {2, 0}, false),Ship(3, {4, 0}, false),Ship(4, {6, 0}, false),Ship(5, {8, 0}, false)};
        player1->placeShips(ships);
        cout << "Placement des bateaux pour " << player2->getName() << endl;
        player2->placeShips(ships);
    }

    IPlayer* getPlayer(int x) const{
        if(x==1) return player1;
        return player2;
    }
};

class Agent : public IPlayer{
    Player* player;
    Game* game;

    Agent(Player* player,Game* game1) : player(player),game(game1){}

    void attack(){
        if (player->grid.grid[0][0] == '~'){
            player->attack(game->getPlayer(2),{0,0});
        }
        player->grid.display();
    }

    void getEnvironment(){

    }
};

int main() {
    Game game("Ordi 1", "Joueur 2");
    game.start();
    game.player1.grid.display();
    game.player1.attack(game.player2, {0, 0});
    game.player2.grid.display();

    return 0;
}