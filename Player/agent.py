class Agent:

    def __init__(self, nom, x, y, gridSize):
        self.nom = nom
        self.x = x
        self.y = y
        self.previous = [x,y]
        self.gridSize = gridSize

    def avancer(self):
        if self.x + 1 < self.gridSize:
            self.previous = [self.x, self.y]
            self.x += 1

    def reculer(self):
        if self.x >= 1:
            self.previous = [self.x, self.y]
            self.x -= 1

    def gauche(self):
        if self.y >= 1:
            self.previous = [self.x, self.y]
            self.y -= 1

    def droite(self):
        if self.y + 1 < self.gridSize:
            self.previous = [self.x, self.y]
            self.y += 1
            
    def collision(self):
        self.x = self.previous[0]
        self.y = self.previous[1]

    def whatToDo(self, i):
        if(i==0):
            self.avancer()
        elif(i==1):
            self.reculer()
        elif(i==2):
            self.gauche()
        else:
            self.droite()
