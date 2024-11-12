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
        //Nombre de défenses restantes
        int nbdefense=1;
        //Constructeur pour la classe Agent
        Agent(string name);
        //Actions :
        //Implémentation de la fonction de placement pour l'agent
        void placeShips() override;
        //Implémentation de la fonction d'attaque pour l'agent
        pair<int,int> attack(IPlayer* player) override;
        //Implémentation de la fonction pour récuperer le prochain coup pour l'agent
        vector<int> prochainCoup();
        void changeCoups(int X, int Y, int valeur);
        void ameliorerCoups(int X, int Y);
        //Implémentation de la fonction de défense 
        vector<int> chooseDefAt();
        //Fonction qui choisit d'attaquer ou défendre
        pair<int,int> whatToDo(IPlayer* player,pair<int,int> coordinates) override;
        //Fonction de défense de l'agent
        void defense(Ship ship, pair<int,int> coordinates, IPlayer* player) override;
        //Lecture :
        //Implémentation des getteurs
        void getEnvironment() override;
        string getName() const override;
        int getNbDefense() override;
        //Implémentation de la détection de touché
        bool isTouched(pair<int,int>coordinates) override;
        //Fonction pour savoir si le bateau aux coordonnées X et Y est le plus grand
        bool isItTheBiggestBoat(pair<int,int> coordinates,vector<int> datas);
};
#endif