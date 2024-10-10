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
                if(grid[(coordinates.second)+i][coordinates.first]=='S')return false;
                X.push_back((coordinates.second)+i);Y.push_back(coordinates.first);
            }
        }
        else {
        for (int i = 0; i < ship.getSize(); i++)
            {
                if(coordinates.second+i>9)return false;
                if(grid[coordinates.second][(coordinates.first)+i]=='S')return false;
                X.push_back((coordinates.second));Y.push_back(coordinates.first+i);
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
    Grid grid;
    Grid play;
        virtual void placeShips()=0;
        virtual void attack(IPlayer* opponent) = 0;
        virtual string getName() const = 0;
        virtual bool isTouched(pair<int,int>coordinates) = 0;
        virtual ~IPlayer(){}
};

class Player : public IPlayer{
public:
    string name;
    Grid grid;
    Grid play;

    Player(string name) : name(name) {}

    void placeShips() {
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
                }while(Y<0 || Y>9);
                cout << "Vertical (v) ou Horizontal (h) ";
                cin >> V;
                if(V=="v")VH=true;
                else VH=false;
                if(i==0 || i==1)bonnePosition=grid.placeShip(Ship(i+2,{X,Y},VH));
                else bonnePosition=grid.placeShip(Ship(i+2,{X,Y},VH));
                grid.display();
            }while(bonnePosition==false);
        }
    }

    void attack(IPlayer* player){
        int X,Y;
        string V;
        bool bonnePosition=true;
        do{play.display();
            if(bonnePosition==false)cout<<"mauvais endroit"<<endl;
            do{
                cout << "Position X (entre 0 et 9) d'attaque " << " : ";
                cin >> X;
                cout << "Position Y (entre 0 et 9) d'attaque " << " : ";
                cin >> Y;
            }while(player->isTouched({Y,X})==true || X>9 || X<0 || Y>9 || Y<0);

        }while(bonnePosition==false);
        if (player->isTouched({Y,X})){
            player->grid.grid[Y][X] = 'X';
            cout << "Touché !" << endl;
        }
        else {
            player->grid.grid[Y][X] = 'O';
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
        player1->placeShips();
        cout << "Placement des bateaux pour " << player2->getName() << endl;
        player2->placeShips();
    }

    IPlayer* getPlayer(int x) const{
        if(x==1) return player1;
        return player2;
    }
};

class Agent : public IPlayer{
    public :
        string name;
        Game* game;
        Grid grid;
        Grid play;

        Agent(string name) : name(name){}

        void placeShips(){
            vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {2, 0}, false),Ship(3, {4, 0}, false),Ship(4, {6, 0}, false),Ship(5, {8, 0}, false)};
            for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i));}
        }

        void attack(Iplayer* player){
            int x,y;
            do{
                x=rand()%10;y=rand()%10;
            }while(player->isTouched({Y,X})==true || X>9 || X<0 || Y>9 || Y<0);
        }

        void getEnvironment(){
            grid.display();
        }
        string getName() const override{
            return name;
        }
        bool isTouched(pair<int,int>coordinates){return true;}
};

int main() {
    Agent p1("Ordi 1");
    Player p2("Joueur 2");
    Game game(&p1, &p2);
    game.start();
    while(game.fin==false){
        game.player1->attack(game.getPlayer(2));
        game.player1->play.display();
        game.fin=game.player2->grid.allSunk();
        if(game.fin==true)break;
        game.player2->attack(game.getPlayer(1));
        game.player2->play.display();
        game.fin=game.player1->grid.allSunk();
    }
    cout<<"fin !"<<endl;

    return 0;
}