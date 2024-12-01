class Environnement:
    grid=[]

    def __init__(self, taille):
        self.taille=taille
        for i in range(0,taille):
            l=[]
            for j in range(0,taille):
                l.append(0)
            self.grid.append(l)

    def afficher(self):
        s=" "
        for i in range(0,4*self.taille+1):
            s+="-"
        print(s)
        for i in range(0,self.taille):
            s=""
            for j in range(0,self.taille):
                s+=" | "+str(self.grid[i][j])
            s+=" |"
            print(s)
            s=" "
            for i in range(0,4*self.taille+1):
                s+="-"
            print(s)
    
