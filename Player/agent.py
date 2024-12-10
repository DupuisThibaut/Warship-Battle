import random

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

    def avancer(self):
        if self.y + 1 < self.gridSize:
            self.previous = [self.x, self.y]
            self.y += 1
            self.move(self.x, self.y)
        else:
            self.collision()

    def reculer(self):
        if self.y >= 1:
            self.previous = [self.x, self.y]
            self.y -= 1
            self.move(self.x, self.y)
        else:
            self.collision()

    def gauche(self):
        if self.x >= 1:
            self.previous = [self.x, self.y]
            self.x -= 1
            self.move(self.x, self.y)
        else:
            self.collision()

    def droite(self):
        if self.x + 1 < self.gridSize:
            self.previous = [self.x, self.y]
            self.x += 1
            self.move(self.x, self.y)
        else:
            self.collision()

    def collision(self):
        tmp = [self.x, self.y]
        self.x = self.previous[0]
        self.y = self.previous[1]
        self.previous = tmp
        self.move(self.x, self.y)

    def collisionObjet(self):
        parcours=[]
        if self.y + 1 < self.gridSize:
            parcours.append(Agent.plusCourtChemin(self,self.x,self.y+1,2))
        #if self.y >= 1:
        #if self.x >= 1:
        #if self.x + 1 < self.gridSize:

    def GoBack(self):
        self.position=0
        if self.x == self.initial_Coordinates[0] and self.y == self.initial_Coordinates[1]:
            print("Est bien revenu")
            self.previous = [self.x, self.y]
            self.back=3
        elif(self.numStrat!=2):
            if self.x > self.initial_Coordinates[0] :
                self.gauche()
            elif self.y > self.initial_Coordinates[1] :
                self.reculer()
            elif self.x < self.initial_Coordinates[0] :
                self.droite()
            elif self.y < self.initial_Coordinates[1] :
                self.avancer()
        elif(self.numStrat==2):
            if self.y > self.initial_Coordinates[1]:
                self.reculer()
            elif self.x > self.initial_Coordinates[0]:
                self.gauche()
            elif self.y < self.initial_Coordinates[1] :
                self.avancer()
            elif self.x < self.initial_Coordinates[0]:
                self.droite()
        else:
            self.previous = [self.x, self.y]
            self.x = self.initial_Coordinates[0]
            self.y = self.initial_Coordinates[1]
        self.move(self.x, self.y)

    def whatToDo(self,grid):
        if(self.cptmove == 0):
            if self.haveToGoBack:
                if self.back==0:
                    self.GoBack()
                else:
                    self.back-=1
                    if self.back==0:
                        self.haveToGoBack=False
            elif self.numStrat == 0:
                self.StratAleat()
            elif self.numStrat == 1:
                self.Stratégie1(grid)
            elif self.numStrat == 2:
                self.Stratégie2(grid)
            elif self.numStrat == 3:
                self.Stratégie3()
            self.cptmove = self.speed 
        else :
            self.previous=[self.x,self.y]
            self.cptmove-=1

    def StratAleat(self):
        i = random.randint(0, 3)
        if i == 0:
            self.avancer()
        elif i == 1:
            self.reculer()
        elif i == 2:
            self.gauche()
        else:
            self.droite()

    def Stratégie1(self,grid):
        if self.x > 0 and self.y==self.initial_Coordinates[1] and grid[self.y][self.x-1] in[" ","X"]:
            self.gauche()
        elif self.y < self.Candy[1] and grid[self.y+1][self.x] in[" ","X"]:
            self.avancer()
        elif self.x < self.Candy[0] and grid[self.y][self.x+1] in[" ","X"]:
            self.droite()
        else :
            self.reculer()

    def Stratégie2(self,grid):
        if self.x < self.gridSize-1 and self.y!=self.Candy[1] and grid[self.y][self.x+1] in[" ","X"]:
            self.droite()
        elif self.y < self.Candy[1] and grid[self.y+1][self.x] in[" ","X"]:
            self.avancer()
        elif self.x > self.Candy[0] and grid[self.y][self.x-1] in[" ","X"]:
            self.gauche()

    def Stratégie3(self):
        if(self.position<=len(self.chemin)-1):
            if self.x<self.chemin[self.position][0]:
                self.droite()
                self.position+=1
            elif self.x>self.chemin[self.position][0]:
                self.gauche()
                self.position+=1
            elif self.y<self.chemin[self.position][1]:
                self.avancer()
                self.position+=1
            elif self.y>self.chemin[self.position][1]:
                self.reculer()
                self.position+=1

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

    def prof(self,eleves):
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
                        self.droite()
                    elif self.x>parcours[0][0]:
                        self.gauche()
                    elif self.y<parcours[0][1]:
                        self.avancer()
                    elif self.y>parcours[0][1]:
                        self.reculer()
                else:
                    parcours=[[self.initial_Coordinates[0],self.initial_Coordinates[1]]]
                    self.previous[0]=self.x
                    self.previous[1]=self.y
                return -1
            if self.x<parcours[0][0]:
                self.droite()
            elif self.x>parcours[0][0]:
                self.gauche()
            elif self.y<parcours[0][1]:
                self.avancer()
            elif self.y>parcours[0][1]:
                self.reculer()
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
