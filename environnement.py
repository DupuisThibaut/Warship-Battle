class Environnement:
    def __init__(self, taille):
        self.taille=taille
        self.grid = []
        for _ in range(taille):
            l = [0 for _ in range(taille)]
            self.grid.append(l)

    def afficher(self):
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

    def displayAgent(self,agent):
        if(self.grid[agent.y][agent.x]==0):
            self.grid[agent.previous[1]][agent.previous[0]] = 0            
            self.grid[agent.y][agent.x]=agent.nom
        else : 
            agent.collision()