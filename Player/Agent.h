#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Iplayer.h"
#include "../Game.h"

using namespace std;
#ifndef AGENT_H
#define AGENT_H

using namespace std;


class Agent : public IPlayer{
    public :
        string name;
        Game* game;

        Agent(string name);

        void placeShips() override;

        void attack(IPlayer* player) override;
        void getEnvironment() override;
        string getName() const override;
        bool isTouched(pair<int,int>coordinates) override;
};
#endif