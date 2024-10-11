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

    bool getSunk(){return isSunk;}
};

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
class IPlayer{
    public:
    Grid grid;
    Grid play;
        virtual void placeShips()=0;
        virtual void attack(IPlayer* opponent) = 0;
        virtual string getName() const = 0;
        virtual bool isTouched(pair<int,int>coordinates) = 0;
        virtual void getEnvironment() = 0;
        void display(){cout<<"Bateau de " << getName() <<endl;grid.display();cout<<"Tir précédent de " << getName() <<endl;play.display();}
        virtual ~IPlayer(){}
};

class Player : public IPlayer{
public:
    string name;

    Player(string name) : name(name) {}

    void placeShips() {
        int X,Y;
        string V;
        bool VH=true;
        bool bonnePosition=true;
        string f;cout << "manuelle ?";cin >> f;if(f=="n"){
            vector<Ship> ships = {Ship(2, {0, 0}, false),Ship(3, {0, 2}, false),Ship(3, {0, 4}, false),Ship(4, {0, 6}, false),Ship(5, {0, 8}, false)};
            for (int i = 0; i < 5; i++){grid.placeShip(ships.at(i),i+1);}
        }else
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
                    if(i==0 || i==1)bonnePosition=grid.placeShip(Ship(i+2,{X,Y},VH),i);
                    else bonnePosition=grid.placeShip(Ship(i+1,{X,Y},VH),i);
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
            }while(X>9 || X<0 || Y>9 || Y<0 || player->grid.grid[Y][X] == 'O' || player->grid.grid[Y][X] == 'X');
        }while(bonnePosition==false);
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

    bool isTouched(pair<int,int>coordinates){
        if (grid.grid[coordinates.first][coordinates.second] != '~' || grid.grid[coordinates.first][coordinates.second] != 'O' || grid.grid[coordinates.first][coordinates.second] != 'X'){
            return true;
        }
        return false;
    }
    string getName() const override {
        return name;
    }

    void getEnvironment(){
            grid.display();
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
        cout << "Lancement de la partie : ";
        char i; cin >> i;
    }

    IPlayer* getPlayer(int x) const{
        if(x==1) return player1;
        return player2;
    }

    void setFin(bool f){
        fin=f;
    }
};

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

int main() {
    Agent a1("Ordi 1");
    Agent a2("Ordi 2");
    Player p1("Joueur 1");
    Player p2("Joueur 2");
    cout << "--------------------" << endl;
    cout << "-- Warship-Battle --" << endl;
    cout << "--------------------" << endl;
    cout << "Mode parte : " << endl;
    cout << "1. Player VS Player " << endl;
    cout << "2. Player VS Agent " << endl;
    cout << "3. Agent VS Player " << endl;
    cout << "4. Agent VS Agent " << endl;
    cout << "Votre choix : ";
    int mode;
    cin >> mode;
    Game* game = nullptr;
    switch (mode) {
        case 1:
            game = new Game(&p1, &p2);
            break;
        case 2:
            game = new Game(&p1, &a1);
            break;
        case 3:
            game = new Game(&a1, &p1);
            break;
        case 4:
            game = new Game(&a1, &a2);
            break;
        default:
            cout << "Mode invalide" << endl;
            return 1;
    }
    game->start();
    int v=2;
    while(game->fin==false){
        cout << "Attaque de " << game->player1->getName() << endl;
        game->player1->attack(game->getPlayer(2));
        game->player1->display();
        game->setFin(game->player2->grid.allSunk());
        if(game->fin==true){v=1;break;}
        cout << "Attaque de " << game->player2->getName() << endl;
        game->player2->attack(game->getPlayer(1));
        game->player2->display();
        game->setFin(game->player1->grid.allSunk());
    }
    if(v==1)cout<<"Victoire de " << game->player1->getName() << " !"<<endl;
    else cout<<"Victoire de " << game->player2->getName() << " !"<<endl;

    return 0;
}
