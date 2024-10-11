#include <iostream>
#include <vector>
#include <string>
#include <random>

//#include "Objects/Ship.cpp"
#include "Objects/Grid.cpp"
#include "Player/IPlayer.cpp"
#include "Player/Player.cpp"
#include "Player/Agent.cpp"

using namespace std;

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
