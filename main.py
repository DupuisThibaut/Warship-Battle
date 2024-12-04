from environnement import Environnement
from Player.agent import Agent
import time
import random

class Main:
    fin=False

    def __init__(self,tailleGrid,agents,teacher):
        self.grid=Environnement(tailleGrid,[random.randint(0,taille-1),random.randint((taille//2)+1,taille-1)])
        self.agents=agents
        print(self.grid.candy)
        for e in self.agents:
            e.Candy = self.grid.candy
            if(e.numStrat==3):
                e.chemin=e.plusCourtChemin(e.Candy[0],e.Candy[1],1)
                print(e.chemin)
        self.debutJeu=time
        self.teacher=teacher

    def updateAgents(self):
        for e in self.agents:
            e.whatToDo()
            self.grid.displayAgent(e)
        i=self.teacher.prof(self.agents)
        if(i!=-1):
            self.agents[i].haveToGoBack=True
        self.grid.displayAgent(self.teacher)
            

taille=10
student1=Agent("Yanis",1,0,taille,1)
student2=Agent("Bastian",8,0,taille,2)
student3=Agent("Thibaut",5,0,taille,3)
students=[student1,student2,student3]
teacher = Agent("I", (taille // 2)-1, (taille // 2), taille,None)
main=Main(taille,students,teacher)
input_test = "ok"
x = 30
start_time = time.time()
main.updateAgents()
main.grid.afficher()
#"""
while True:
    elapsed_time = time.time() - start_time
    if elapsed_time > x:
        print("Temps écoulé. Fin du jeu.")
        break
    main.updateAgents()
    main.grid.afficher()
    time.sleep(1)
maxPoint=0
bestStudent = student1
for e in students:
    print(f"{e.nom} marque : {e.nbPoint} point(s) avec la stratégie {e.numStrat}")
    if(e.nbPoint>maxPoint):
        bestStudent = e
        maxPoint = e.nbPoint
print(f"Victoire de {bestStudent.nom} : La meilleure stratégie est la {bestStudent.numStrat}")
#"""