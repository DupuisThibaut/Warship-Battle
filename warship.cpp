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

    bool placeShip(Ship ship) {
        pair<int, int> coordinates = ship.getCoordinates();
        bool isVertical = ship.getIsVertical();
        ship.placeShip(coordinates,isVertical);
        vector<int> X;
        vector<int> Y;
        if (isVertical){
            for (int i = 0; i < ship.getSize(); i++)
            {
                if(coordinates.first+i>9)return false;
                if(grid[(coordinates.first)+i][coordinates.second]=='S')return false;
                X.push_back((coordinates.first)+i);Y.push_back(coordinates.second);
            }
        }
        else {
        for (int i = 0; i < ship.getSize(); i++)
            {
                if(coordinates.second+i>9)return false;
                if(grid[coordinates.first][(coordinates.second)+i]=='S')return false;
                X.push_back((coordinates.first));Y.push_back(coordinates.second+i);
            }
        }
        for (int i = 0; i < ship.getSize(); i++){
            grid[X[i]][Y[i]] = 'S';
        }
        ships.push_back(ship);
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

    bool allSunk(){
        for(int i=0;i<5;i++){
            if(ships[i].isSunk==false)return false;
        }return true;
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
    bool fin=false;

    Game(IPlayer* p1, IPlayer* p2) : player1(p1), player2(p2) {}

    void start() {
        cout << "Placement des bateaux pour " << player1->getName() << endl;
        int X,Y;
        string V;
        bool VH=true;
        bool bonnePosition=true;
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
                }while(X<0 || X>9);
                cout << "Vertical (v) ou Horizontal (h) ";
                cin >> V;
                if(V=="v")VH=true;
                if(i==0 || i==1)bonnePosition=player1.grid.placeShip(Ship(i+2,{X,Y},VH));
                else bonnePosition=player1.grid.placeShip(Ship(i+2,{X,Y},VH));
            }while(bonnePosition==false);
        }
        cout << "Placement des bateaux pour " << player2->getName() << endl;
        VH=false;
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
                }while(X<0 || X>9);
                cout << "Vertical (v) ou Horizontal (h) ";
                cin >> V;
                if(V=="v")VH=true;
                if(i==0 || i==1)bonnePosition=player2.grid.placeShip(Ship(i+2,{X,Y},VH));
                else bonnePosition=player2.grid.placeShip(Ship(i+2,{X,Y},VH));
            }while(bonnePosition==false);
        }
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
    while(game.fin==false){
        int X,Y;
        cout << "Joueur 1 attaque ligne : ";
        cin >> X;
        cout << "Joueur 1 attaque colonne : ";
        cin >> Y;
        game.player1.attack(game.player2, {X,Y});
        game.player1.grid.display();
        fin=game.player2.grid.allSunk();
        if(fin==true)break;
        cout << "Joueur 2 attaque ligne : ";
        cin >> X;
        cout << "Joueur 2 attaque colonne : ";
        cin >> Y;
        game.player2.attack(game.player1, {X,Y});
        game.player2.grid.display();
        fin=game.player1.grid.allSunk();
    }
    cout<<"fin !"<<endl;

    return 0;
}