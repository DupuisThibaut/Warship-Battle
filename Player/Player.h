#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "../Objects/Ship.h"
#include "../Objects/Grid.h"
#include "Iplayer.h"

using namespace std;
#ifndef PLAYER_H
#define PLAYER_H

class Player : public IPlayer{
public:
    string name;

    Player(string name);

    void placeShips() override;
    void attack(IPlayer* player)override;

    bool isTouched(pair<int,int>coordinates) override;
    string getName() const override;
	void setName(string newName);

    void getEnvironment() override;
};
#endif