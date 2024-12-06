from environnement import Environnement
from Player.agent import Agent
import time
import random
import pygame

pygame.init()
WIDTH = 500
HEIGHT = 500
TAILLE = 10
TAILLE_CASE = WIDTH // TAILLE
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
candy_position = (0, 0)
img_candy = pygame.image.load("img/skins/candy.png") 
img_candy = pygame.transform.scale(img_candy, (TAILLE_CASE, TAILLE_CASE))

def draw_image1(x, y):
    screen.blit(img_candy, (x * TAILLE_CASE, y * TAILLE_CASE))

def update_image1_position(new_x, new_y):
    global candy_position
    candy_position = (new_x, new_y)

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Jeu des narvalos")

def draw_board():
    """Dessine le damier."""
    for row in range(TAILLE):
        for col in range(TAILLE):
            color = WHITE if (row + col) % 2 == 0 else BLACK
            pygame.draw.rect(screen, color, (col * TAILLE_CASE, row * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE))

class Img_Agent:
    def __init__(self,img,x,y):
        self.x=x 
        self.y=y
        self.position = (self.x, self.y)
        self.img = pygame.image.load("img/skins/"+img+".png") 
        self.img = pygame.transform.scale(self.img, (TAILLE_CASE, TAILLE_CASE))

    def draw(self):
        screen.blit(self.img, (self.x * TAILLE_CASE, self.y * TAILLE_CASE))

    def update_position(self,new_x, new_y):
        self.x = new_x
        self.y = new_y    

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
            

taille=TAILLE

#Définitions de student1
img_student1=Img_Agent("student1",1,0)
student1=Agent("Yanis",1,0,taille,1,img_student1.update_position)

#Définitions de student2
img_student2=Img_Agent("student2",8,0)
student2=Agent("Bastian",8,0,taille,2,img_student2.update_position)

#Définitions de student3
img_student3=Img_Agent("student3",5,0)
student3=Agent("Thibaut",5,0,taille,3,img_student3.update_position)

#Définitions de student4
img_student4=Img_Agent("student4",6,0)
student4=Agent("G",6,0,taille,0,img_student4.update_position)

students=[student1,student2,student3,student4]

#Définitions de teacher
img_teacher=Img_Agent("teacher",(taille // 2)-1,(taille // 2))
teacher = Agent("I", (taille // 2)-1, (taille // 2), taille,None,img_teacher.update_position)
main=Main(taille,students,teacher)
input_test = "ok"
x = 30
start_time = time.time()
main.updateAgents()
main.grid.afficher()
#"""
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    main.updateAgents()
    main.grid.afficher()
    time.sleep(1)
    draw_board()
    update_image1_position(*main.grid.candy)
    draw_image1(*candy_position)
    img_student1.draw()
    img_student2.draw()
    img_student3.draw()
    img_student4.draw()
    img_teacher.draw()
    pygame.display.flip()

# Quitter Pygame
pygame.quit()

#while True:
#    elapsed_time = time.time() - start_time
#    if elapsed_time > x:
 #       print("Temps écoulé. Fin du jeu.")
 #       break
  #  main.updateAgents()
 #   main.grid.afficher()
#    time.sleep(1)

maxPoint=0
bestStudent = student1
for e in students:
    print(f"{e.nom} marque : {e.nbPoint} point(s) avec la stratégie {e.numStrat}")
    if(e.nbPoint>maxPoint):
        bestStudent = e
        maxPoint = e.nbPoint
print(f"Victoire de {bestStudent.nom} : La meilleure stratégie est la {bestStudent.numStrat}")
#"""
