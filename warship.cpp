#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Objects/Ship.h"
#include "Objects/Grid.h"
#include "Player/Player.h"
#include "Player/Agent.h"
#include "Player/Iplayer.h"
#include "Game.h"

using namespace std;

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
    string name;
	cin >> mode;
	Game* game = nullptr;
	switch (mode) {
		case 1:
			cout << "Entrer le nom du Joueur 1 : ";
			cin >> name;
			p1.setName(name);
			cout << "Entrer le nom du Joueur 2 : ";
			cin >> name;
			p2.setName(name);
			game = new Game(&p1, &p2);
			break;
		case 2:
			cout << "Entrer le nom du Joueur 1 : ";
			cin >> name;
			p1.setName(name);
			game = new Game(&p1, &a1);
			break;
		case 3:
			cout << "Entrer le nom du Joueur 1 : ";
			cin >> name;
			p1.setName(name);
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
    pair<int,int> coordinates = make_pair(10,10);
    while(game->fin==false){
        cout << "Attaque de " << game->player1->getName() << endl;
        coordinates = game->player1->whatToDo(game->getPlayer(2),coordinates);
        game->player1->display();
        game->setFin(game->player2->grid.allSunk());
        if(game->fin==true){v=1;break;}
        cout << "Attaque de " << game->player2->getName() << endl;
        coordinates = game->player2->whatToDo(game->getPlayer(1),coordinates);
        game->player2->display();
        game->setFin(game->player1->grid.allSunk());
        //char i;cin>>i;
    }
    cout<<"Il reste "<<game->player1->getNbDefense()<<" au joueur 1"<<endl;
    cout<<"Il reste "<<game->player2->getNbDefense()<<" au joueur 2"<<endl;
    if(v==1)cout<<"Victoire de " << game->player1->getName() << " !"<<endl;
    else cout<<"Victoire de " << game->player2->getName() << " !"<<endl;

    return 0;
}