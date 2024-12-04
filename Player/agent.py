import random

class Agent:

    def __init__(self, nom, x, y, gridSize, numStrat):
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

    def avancer(self):
        if self.y + 1 < self.gridSize:
            self.previous = [self.x, self.y]
            self.y += 1
        else:
            self.collision()

    def reculer(self):
        if self.y >= 1:
            self.previous = [self.x, self.y]
            self.y -= 1
        else:
            self.collision()

    def gauche(self):
        if self.x >= 1:
            self.previous = [self.x, self.y]
            self.x -= 1
        else:
            self.collision()

    def droite(self):
        if self.x + 1 < self.gridSize:
            self.previous = [self.x, self.y]
            self.x += 1
        else:
            self.collision()
            
    def collision(self):
        tmp = [self.x, self.y]
        self.x = self.previous[0]
        self.y = self.previous[1]
        self.previous = tmp
    
    def GoBack(self):
        if self.x > self.initial_Coordinates[0] and self.Candy[0]!=self.x-1:
            self.gauche()
        elif self.x < self.initial_Coordinates[0] and self.Candy[0]!=self.x+1:
            self.droite()
        elif self.y > self.initial_Coordinates[1] and self.Candy[1]!=self.y-1:
            self.reculer()
        elif self.y < self.initial_Coordinates[1]and self.Candy[1]!=self.y+1:
            self.avancer()
        elif self.x == self.initial_Coordinates[0] and self.y == self.initial_Coordinates[1]:
            print("Est bien revenu")
            self.previous = [self.x, self.y]
            self.haveToGoBack = False
        else:
            self.previous = [self.x, self.y]
            self.x = self.initial_Coordinates[0]
            self.y = self.initial_Coordinates[1]

    def whatToDo(self):
        if self.haveToGoBack:
            self.GoBack()

        elif self.numStrat == 0:
            self.StratAleat()
        elif self.numStrat == 1:
            self.Stratégie1()
    
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
    
    def Stratégie1(self):
        if self.x > 0 and self.y!=self.Candy[1]:
            self.gauche()
        elif self.y < self.Candy[1]:
            self.avancer()
        elif self.x < self.Candy[0]:
            self.droite()
        elif self.y > self.Candy[1]:
            self.reculer()
        elif self.x > self.Candy[0]:
            self.gauche()

