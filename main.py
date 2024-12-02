from environnement import Environnement
from Player.agent import Agent
import time
import random

class Main:
    fin=False

    def __init__(self,tailleGrid,agents):
        self.grid=Environnement(tailleGrid)
        self.agents=agents
        self.debutJeu=time

    def updateAgents(self):
        for e in self.agents:
            random_number = random.randint(0, 3)
            e.whatToDo(random_number)
            self.grid.displayAgent(e)
    


taille=20
agent1=Agent("1",2,0,taille)
agent2=Agent("2",1,1,taille)
agent3=Agent("3",2,2,taille)
agents=[agent1,agent2,agent3]
main=Main(taille,agents)
input_test = "ok"
x = 10
start_time = time.time()
while True:
    elapsed_time = time.time() - start_time
    if elapsed_time > x:
        print("Temps écoulé. Fin du jeu.")
        break
    main.updateAgents()
    main.grid.afficher()
    time.sleep(1)