#include <iostream>
#include <vector>
#include <string>
#include <random>

//#include "Objects/Ship.cpp"
#include "Objects/Grid.cpp"

using namespace std;

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

