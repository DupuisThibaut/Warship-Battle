class Environnement:
    def __init__(self, taille,coordinates):
        self.taille=taille
        self.grid = []
        self.candy = coordinates
        for _ in range(taille):
            l = [" " for _ in range(taille)]
            self.grid.append(l)
        self.grid[self.candy[1]][self.candy[0]] = "X"

    def afficher(self):
        print("\033[H\033[J", end="")
        s=" "
        for _ in range(4*self.taille+1):
            s+="-"
        print(s)
        for i in range(self.taille):
            s = "".join(f" | {str(self.grid[i][j])}" for j in range(self.taille)) + " |"
            print(s)
            s=" "
            for _ in range(4*self.taille+1):
                s+="-"
            print(s)
        print(" ")

    def displayAgent(self,agent):
        if (self.grid[agent.y][agent.x]==" "):
            self.grid[agent.previous[1]][agent.previous[0]] = " "
            self.grid[agent.y][agent.x]=agent.nom[0]
        elif([agent.x,agent.y]==self.candy and agent.haveToGoBack==False):
            agent.nbPoint+=1
            agent.haveToGoBack = True
            agent.collision()
        else: 
            agent.collision()