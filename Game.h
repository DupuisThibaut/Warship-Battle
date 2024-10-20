#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Player/Iplayer.h"

using namespace std;
#ifndef GAME_H
#define GAME_H

using namespace std;

class Game {
public:

    IPlayer* player1;
    IPlayer* player2;
    bool fin=false;

    Game(IPlayer* p1, IPlayer* p2);

    void start();

    IPlayer* getPlayer(int x) const;

    void setFin(bool f);
};
#endif