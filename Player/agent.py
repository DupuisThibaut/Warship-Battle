import random
import math

class Agent:

    def __init__(self, nom, x, y, gridSize, numStrat, move,speed=5):
        self.nom = nom
        self.x = x  # Position horizontale (colonnes)
        self.y = y  # Position verticale (lignes)
        self.previous = [x, y]
        self.gridSize = gridSize
        self.nbPoint = 0
        self.initial_Coordinates = [x, y]
        self.haveToGoBack = False
        self.numStrat = numStrat
        self.Candy = [0, 0]
        self.teacher = []
        self.chemin = []
        self.position=0
        self.back=0
        self.move = move
        self.speed = speed
        self.cptmove = self.speed
        self.grid=None
        self.retour=[[x,y]]

    def avancer(self,grid):
        if self.y + 1 < self.gridSize:
            if grid[self.y + 1][self.x] not in ["O"]:
                self.previous = [self.x, self.y]
                self.y += 1
            else:
                self.collision(1,grid)
        else:
            self.collision(1,grid)

    def reculer(self,grid):
        if self.y >= 1:
            if grid[self.y - 1][self.x] not in ["O"]:
                self.previous = [self.x, self.y]
                self.y -= 1
            else:
                self.collision(2,grid)
        else:
            self.collision(2,grid)

    def gauche(self,grid):
        if self.x >= 1:
            if grid[self.y][self.x - 1] not in ["O"]:
                self.previous = [self.x, self.y]
                self.x -= 1
            else:
                self.collision(3,grid)
        else:
            self.collision(3,grid)

    def droite(self,grid):
        if self.x + 1 < self.gridSize:
            if grid[self.y][self.x + 1] not in ["O"]:
                self.previous = [self.x, self.y]
                self.x += 1
            else:
                self.collision(4,grid)
        else:
            self.collision(4,grid)

    def collision(self, provenance=0, grid=None):
        tmp = [self.x, self.y]
        if provenance != 0 and grid is not None:
            parcours = self.collisionObjet(provenance, grid)
        else:
            parcours = [tmp]

        if parcours and parcours[0] != tmp:
            self.x = parcours[0][0]
            self.y = parcours[0][1]
        else:
            self.x = self.previous[0]
            self.y = self.previous[1]
        # Empêcher les coordonnées invalides
        self.x = max(self.x, 0)
        self.y = max(self.y, 0)
        self.previous = tmp
        self.move(self.x, self.y)

    def collisionObjet(self, provenance, grid):
        parcours = [[self.x, self.y]]
        chemin = []
        min0 = self.gridSize * self.gridSize
        directions = [
            (self.y + 1, self.x, 1),  # Bas
            (self.y - 1, self.x, 2),  # Haut
            (self.y, self.x - 1, 3),  # Gauche
            (self.y, self.x + 1, 4)   # Droite
        ]

        for new_y, new_x, prov in directions:
            if 0 <= new_y < self.gridSize and 0 <= new_x < self.gridSize and provenance != prov and grid[new_y][new_x] == " ":
                chemin = self.plusCourtChemin2(new_x, new_y)
                if len(chemin) < min0:
                    min0 = len(chemin)
                    parcours = chemin

        return parcours or [[self.x, self.y]]



    def GoBack(self, grid):
        self.position = 0
        if self.x == self.initial_Coordinates[0] and self.y == self.initial_Coordinates[1]:
            print("Est bien revenu")
            self.previous = [self.x, self.y]
            self.back = 3
            self.retour=[self.initial_Coordinates]
        elif(self.nom=="teacher"):
            if self.x > self.initial_Coordinates[0] and not((self.x - 1 >= 0 and grid[self.y][self.x - 1] == "X") or (self.x + 1 < self.gridSize and grid[self.y][self.x + 1] == "X")):
                self.gauche(grid)
            elif self.x < self.initial_Coordinates[0] and not((self.x - 1 >= 0 and grid[self.y][self.x - 1] == "X") or (self.x + 1 < self.gridSize and grid[self.y][self.x + 1] == "X")):
                self.droite(grid)
            elif self.y > self.initial_Coordinates[1] or ((self.x - 1 >= 0 and grid[self.y][self.x - 1] == "X") or (self.x + 1 < self.gridSize and grid[self.y][self.x + 1] == "X")):
                self.reculer(grid)
            elif self.y < self.initial_Coordinates[1] or ((self.x - 1 >= 0 and grid[self.y][self.x - 1] == "X") or (self.x + 1 < self.gridSize and grid[self.y][self.x + 1] == "X")):
                self.avancer(grid)
            self.move(self.x, self.y)
        else:
            self.previous = [self.x, self.y]
            tmp = self.retour.pop() if(self.retour!=[]) else self.initial_Coordinates
            self.x = tmp[0]
            self.y = tmp[1]




    def whatToDo(self,grid):
        self.grid=grid
        if(self.cptmove == 0):
            if self.haveToGoBack:
                if self.back==0:
                    self.GoBack(grid)
                else:
                    self.back-=1
                    if self.back==0:
                        self.haveToGoBack=False
            elif self.numStrat == 0:
                self.Stratégie4(grid)
            elif self.numStrat == 1:
                self.Stratégie1(grid)
            elif self.numStrat == 2:
                self.Stratégie2(grid)
            elif self.numStrat == 3:
                self.Stratégie3(grid)
            self.cptmove = self.speed
        else :
            self.previous=[self.x,self.y]
            self.cptmove-=1

    def StratAleat(self,grid):
        i = random.randint(0, 3)
        if i == 0:
            self.avancer(grid)
        elif i == 1:
            self.reculer(grid)
        elif i == 2:
            self.gauche(grid)
        else:
            self.droite(grid)

    def Stratégie1(self,grid):
        if self.x > 0 and self.y==self.initial_Coordinates[1]:
            self.gauche(grid)
        elif self.y < self.Candy[1]:
            self.avancer(grid)
        elif self.x < self.Candy[0]:
            self.droite(grid)
        else :
            self.reculer(grid)

    def Stratégie2(self,grid):
        if self.x < self.gridSize-1 and self.y!=self.Candy[1]:
            self.droite(grid)
        elif self.y < self.Candy[1]:
            self.avancer(grid)
        elif self.x > self.Candy[0]:
            self.gauche(grid)
        else :
            self.reculer(grid)

    def Stratégie3(self, grid):
        self.chemin = self.plusCourtChemin(self.Candy[0], self.Candy[1], 1)
        if self.chemin:  # Vérifier que le chemin n'est pas vide
            if self.x < self.chemin[0][0]:
                self.droite(grid)
            elif self.x > self.chemin[0][0]:
                self.gauche(grid)
            elif self.y < self.chemin[0][1]:
                self.avancer(grid)
            elif self.y > self.chemin[0][1]:
                self.reculer(grid)

    def Stratégie4(self, grid):
        min1=self.gridSize*self.gridSize*self.gridSize
        suivant=[]
        if self.x+1<self.gridSize:
            if grid[self.y][self.x+1] not in ["O","I"] and self.previous!=[self.x+1,self.y]:
                a=(self.Candy[0]-(self.x+1))**2+(self.Candy[1]-self.y)**2
                if min1>a:
                    min1=a
                    suivant=[self.x+1,self.y]
        if self.x-1>0:
            if grid[self.y][self.x-1] not in ["O","I"] and self.previous!=[self.x-1,self.y]:
                a=(self.Candy[0]-(self.x-1))**2+(self.Candy[1]-self.y)**2
                if min1>a:
                    min1=a
                    suivant=[self.x-1,self.y]
        if self.y+1<self.gridSize:
            if grid[self.y+1][self.x] not in ["O","I"] and self.previous!=[self.x,self.y+1]:
                a=(self.Candy[0]-self.x)**2+(self.Candy[1]-(self.y+1))**2
                if min1>a:
                    min1=a
                    suivant=[self.x,self.y+1]
        print(min1)
        if suivant:
            self.previous = [self.x, self.y]
            self.x=suivant[0]
            self.y=suivant[1]


    def plusCourtChemin(self,x,y,chemin):
        agentX=self.x
        agentY=self.y
        l=[]
        if(chemin==1):
            avance=True
            while(agentX!=x or agentY!=y):
                if agentX==x or agentY==y:
                    if agentY < y:
                        agentY+=1
                        l.append([agentX,agentY])
                    elif agentY > y:
                        agentY-=1
                        l.append([agentX,agentY])
                    elif agentX < x:
                        agentX+=1
                        l.append([agentX,agentY])
                    elif agentX > x:
                        agentX-=1
                        l.append([agentX,agentY])
                elif(avance):
                    if agentY < y:
                        agentY+=1
                        l.append([agentX,agentY])
                        avance=False
                    elif agentY > y:
                        agentY-=1
                        l.append([agentX,agentY])
                        avance=False
                else:
                    if agentX < x:
                        agentX+=1
                        l.append([agentX,agentY])
                        avance=True
                    elif agentX > x:
                        agentX-=1
                        l.append([agentX,agentY])
                        avance=True
        elif(chemin==2):
            while(agentX!=x):
                if agentX < x:
                    agentX+=1
                    l.append([agentX,agentY])
                    avance=True
                elif agentX > x:
                    agentX-=1
                    l.append([agentX,agentY])
                    avance=True
            while(agentY!=y):
                if agentY < y:
                    agentY+=1
                    l.append([agentX,agentY])
                    avance=False
                elif agentY > y:
                    agentY-=1
                    l.append([agentX,agentY])
                    avance=False
        elif(chemin==3):
            while(agentY!=y):
                if agentY < y:
                    agentY+=1
                    l.append([agentX,agentY])
                    avance=False
                elif agentY > y:
                    agentY-=1
                    l.append([agentX,agentY])
                    avance=False
            while(agentX!=x):
                if agentX < x:
                    agentX+=1
                    l.append([agentX,agentY])
                    avance=True
                elif agentX > x:
                    agentX-=1
                    l.append([agentX,agentY])
                    avance=True
        return l

    def plusCourtChemin2(self,x,y):
        a=Agent(self.nom,x,y,self.gridSize,self.numStrat,self.move,self.speed)
        return a.plusCourtChemin(self.Candy[0],self.Candy[1],self.numStrat)

    def prof(self,eleves,grid):
        if (self.cptmove==0):
            self.cptmove=self.speed
            for e in range(len(eleves)):
                if (self.x > 0 and eleves[e].x == self.x - 1 and eleves[e].y == self.y and eleves[e].haveToGoBack == False):
                    self.previous=[self.x,self.y]
                    return e
                if (self.x < self.gridSize and eleves[e].x == self.x + 1 and eleves[e].y == self.y and eleves[e].haveToGoBack == False):
                    self.previous=[self.x,self.y]
                    return e
                if (self.y > 0 and eleves[e].y == self.y - 1 and eleves[e].x == self.x and eleves[e].haveToGoBack == False):
                    self.previous=[self.x,self.y]
                    return e
                if (self.y < self.gridSize and eleves[e].y == self.y + 1 and eleves[e].x == self.x and eleves[e].haveToGoBack == False):
                    self.previous=[self.x,self.y]
                    return e
            min1=self.gridSize*self.gridSize
            parcours=[]
            e=-1
            for i, eleve in enumerate(eleves):
                if(eleve.haveToGoBack==False):
                    l=Agent.plusCourtChemin(self,eleve.x,eleve.y,2)
                    if len(l)<min1:
                        min1=len(l)
                        parcours=l
                        e=i
            parcoursVide=False
            if parcours==[]:
                parcoursVide=True
                if self.x!=self.initial_Coordinates[0] or self.y!=self.initial_Coordinates[1]:
                    parcours=Agent.plusCourtChemin(self,self.initial_Coordinates[0],self.initial_Coordinates[1],2)
                    if self.x<parcours[0][0]:
                        self.droite(grid)
                    elif self.x>parcours[0][0]:
                        self.gauche(grid)
                    elif self.y<parcours[0][1]:
                        self.avancer(grid)
                    elif self.y>parcours[0][1]:
                        self.reculer(grid)
                else:
                    parcours=[[self.initial_Coordinates[0],self.initial_Coordinates[1]]]
                    self.previous[0]=self.x
                    self.previous[1]=self.y
                return -1
            if self.x<parcours[0][0]:
                self.droite(grid)
            elif self.x>parcours[0][0]:
                self.gauche(grid)
            elif self.y<parcours[0][1]:
                self.avancer(grid)
            elif self.y>parcours[0][1]:
                self.reculer(grid)
            if self.x>0:
                if eleves[e].x==self.x-1 and eleves[e].y==self.y:
                    return e
            elif self.x<self.gridSize:
                if eleves[e].x==self.x+1 and eleves[e].y==self.y:
                    return e
            elif self.y>0:
                if eleves[e].y==self.y-1 and eleves[e].x==self.x:
                    return e
            elif self.y<self.gridSize:
                if eleves[e].y==self.y+1 and eleves[e].x==self.x:
                    return e
        else:
            self.previous=[self.x,self.y]
            self.cptmove-=1
        return -1
