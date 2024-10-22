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

//Classe qui étend IPlayer et qui désigne l'agent (joueur non humain)
class Agent : public IPlayer{
    public :
        //Nom de l'agent
        string name;
        //Environnement dans lequel il se trouve
        Game* game;
        //Liste des prochains coups
        vector<int> coups;
        //Constructeur pour la classe Agent
        Agent(string name);
        //Actions :
        //Implémentation de la fonction de placement pour l'agent
        void placeShips() override;
        //Implémentation de la fonction d'attaque pour l'agent
        void attack(IPlayer* player) override;
        //Implémentation de la fonction pour récuperer le prochain coup pour l'agent
        vector<int> prochainCoup();
        //Lecture :
        //Implémentation des getteurs
        void getEnvironment() override;
        string getName() const override;
        //Implémentation de la détection de touché
        bool isTouched(pair<int,int>coordinates) override;
};
#endif