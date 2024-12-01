from environnement import Environnement
from agent import Agent
import time

class Main:
    fin=False

    def __init__(self,tailleGrid,agents):
        self.grid=Environnement(tailleGrid)
        self.agents=agents
        self.debutJeu=time

agent1=Agent("1",0,0)
agent2=Agent("2",1,1)
agent3=Agent("3",2,2)
agents=[agent1,agent2,agent3]
taille=20
main=Main(taille,agents)
main.grid.afficher()
while(main.fin==False):
    for i in range(0,len(agents)):
        #main.agents[i].prochainCoup()
        print(i)