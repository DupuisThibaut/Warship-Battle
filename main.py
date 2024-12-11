import itertools
from environnement import Environnement
from Player.agent import Agent
import time
import random
import pygame
import os
import sys

def resource_path(relative_path):
    try:
        base_path = sys._MEIPASS
    except AttributeError:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)

pygame.init()
WIDTH = 500
HEIGHT = WIDTH+50
TAILLE = 10
TAILLE_CASE = WIDTH // TAILLE
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BACKGROUND = (40, 40, 40)
SOL = (220, 220, 220)

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Jeu des bonbons")
OFFSET_X = WIDTH // 2
OFFSET_Y = HEIGHT // 4

def draw_board(couleur1=SOL, couleur2=SOL):
    """Dessine un sol avec des carreaux et des lignes noires."""
    board = pygame.Rect(0, 0, WIDTH, WIDTH)
    pygame.draw.rect(screen, SOL, board)
    for row, col in itertools.product(range(TAILLE), range(TAILLE)):
        pygame.draw.rect(screen, (150,150,150), (col * TAILLE_CASE, row * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE), 1)

class Img_Agent:
    def __init__(self,img,x,y):
        self.x=x
        self.y=y
        self.position = (self.x, self.y)
        self.img = pygame.image.load(resource_path("img/skins/"+img+".png"))
        self.img = pygame.transform.scale(self.img, (TAILLE_CASE, TAILLE_CASE))

    def draw(self):
        screen.blit(self.img, (self.x * TAILLE_CASE, self.y * TAILLE_CASE))

    def update_position(self,new_x, new_y):
        self.x = new_x
        self.y = new_y

    def resize(self):
        self.img = pygame.transform.scale(self.img, (TAILLE_CASE, TAILLE_CASE))

class Main:
    fin=False

    def __init__(self,tailleGrid,agents,teacher,obstacles):
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
        self.obstacles=obstacles

    def updateAgents(self):
        for e in self.obstacles:
            self.grid.displayAgent(e)
        for e in self.agents:
            e.whatToDo(self.grid.grid)
            self.grid.displayAgent(e)
        i=self.teacher.prof(self.agents,self.grid.grid)
        if(i!=-1):
            self.agents[i].haveToGoBack=True
        self.grid.displayAgent(self.teacher)


taille=TAILLE
students=[]
list_Img=[]
obstacles=[]
teachers=[]
x = 30
y = 4
z = 10

def create_Agent(n):
    for i in range(n):
        x=(i*2)%(taille-2)+1
        y=(i//((taille-2)//2))*3
        img_student = Img_Agent(f"student{str(i % 4 + 1)}", x, y)
        student = Agent(
            f"{str(i + 1)}", x, y, taille, i % 4, img_student.update_position
        )
        students.append(student)
        list_Img.append(img_student)
        img_obstacle=Img_Agent("obstacle",x,y+1)
        list_Img.append(img_obstacle)
        obstacle=Agent("O",x,y+1,taille,None,img_obstacle.update_position)
        obstacles.append(obstacle)

    img_teacher=Img_Agent("teacher",(taille // 2)-1,(taille // 2))
    teacher = Agent("I", (taille // 2)-1, (taille // 2), taille,None,img_teacher.update_position,z)
    teachers.append(teacher)

    list_Img.append(img_teacher)

font2=pygame.font.Font(None, 24)
font = pygame.font.Font(None, 74)
small_font = pygame.font.Font(None, 36)

img_candy = pygame.image.load(resource_path("img/skins/candy.png"))
img_candy = pygame.transform.scale(img_candy, (TAILLE_CASE, TAILLE_CASE))

def draw_candy(x, y):
    screen.blit(img_candy, (x * TAILLE_CASE, y * TAILLE_CASE))

input_test = "ok"
start_time = time.time()

#"""
running = True
state="menu"
while running:
    screen.fill(BACKGROUND)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if state=="menu":
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = event.pos
                if start_button.collidepoint(mouse_pos):
                    state = "option"
                elif quit_button.collidepoint(mouse_pos):
                    running = False
        elif state=="option":
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = event.pos
                if start_button2.collidepoint(mouse_pos):
                    start_time = time.time()
                    create_Agent(y)
                    state = "game"
                    main=Main(taille,students,teachers[0],obstacles)
                    candy_position = main.grid.candy
                elif quit_button2.collidepoint(mouse_pos):
                    running = False
                elif uptime_button.collidepoint(mouse_pos):
                    x += 10
                elif downtime_button.collidepoint(mouse_pos):
                    x -= 10
                elif downsize_button.collidepoint(mouse_pos):
                    TAILLE-=1
                    taille = TAILLE
                    TAILLE_CASE = WIDTH // TAILLE
                    for e in list_Img :
                        e.resize()
                    img_candy = pygame.transform.scale(img_candy, (TAILLE_CASE, TAILLE_CASE))
                elif upsize_button.collidepoint(mouse_pos):
                    TAILLE+=1
                    taille = TAILLE
                    TAILLE_CASE = WIDTH // TAILLE
                    for e in list_Img :
                        e.resize()
                    img_candy = pygame.transform.scale(img_candy, (TAILLE_CASE, TAILLE_CASE))
                elif upagent_button.collidepoint(mouse_pos):
                    if(y<taille-2):
                        y += 1
                elif downagent_button.collidepoint(mouse_pos):
                    if(y>1):
                        y -= 1
                elif upspeed_button.collidepoint(mouse_pos):
                    z +=1
                elif downspeed_button.collidepoint(mouse_pos):
                    if(z>1):
                       z -=1
    if state == "game":
        elapsed_time = time.time() - start_time
        if elapsed_time > x:
            running = False
        draw_board()
        draw_candy(*candy_position)
        for e in list_Img:
            e.draw()
        main.grid.afficher()
        main.updateAgents()
        text1 = font2.render(main.grid.msg,1,(255,255,255))
        text2 = font2.render(f"{int(elapsed_time)} / {str(x)}s", 1, (255, 255, 255))
        screen.blit(text1, (10, 510))
        screen.blit(text2, (10, 530))
        time.sleep(0.1)
    elif state == "menu":
        titre = font.render("Menu Principal", True, WHITE)
        start_text = small_font.render("Démarrer le jeu", True, WHITE)
        quit_text = small_font.render("Quitter", True, WHITE)
        start_button = pygame.Rect(60, 200, 380, 50)
        quit_button = pygame.Rect(60, 300, 380, 50)
        pygame.draw.rect(screen, BLUE, start_button)
        pygame.draw.rect(screen, RED, quit_button)
        screen.blit(start_text, (150, 210))
        screen.blit(quit_text, (150, 310))
        screen.blit(titre, (60, 100))
    elif state == "option":
        titre2 = font.render("Options", True, WHITE)
        start_text2 = small_font.render("Démarrer le jeu", True, WHITE)
        quit_text2 = small_font.render("Quitter", True, WHITE)
        time_texte = small_font.render(f"Temps de jeux : {x}", True, WHITE)
        size_texte = small_font.render(f"Taille du plateau : {str(taille)}", True, WHITE)
        nbA_texte = small_font.render(f"Nombre d'élèves : {y}", True, WHITE)
        speed_texte = small_font.render(f"Vitesse : {z}", True, WHITE)
        start_button2 = pygame.Rect(60, 380, 380, 50)
        quit_button2 = pygame.Rect(60, 480, 380, 50)
        downtime_button = pygame.Rect(300, 170, 25, 25)
        uptime_button = pygame.Rect(350, 170, 25, 25)
        downsize_button = pygame.Rect(300, 220, 25, 25)
        upsize_button = pygame.Rect(350, 220, 25, 25)
        downagent_button = pygame.Rect(300, 270, 25, 25)
        upagent_button = pygame.Rect(350, 270, 25, 25)
        downspeed_button = pygame.Rect(300, 320, 25, 25)
        upspeed_button = pygame.Rect(350, 320, 25, 25)
        pygame.draw.rect(screen, BLUE, start_button2)
        pygame.draw.rect(screen, RED, quit_button2)
        pygame.draw.rect(screen, RED, downtime_button)
        pygame.draw.rect(screen, GREEN, uptime_button)
        pygame.draw.rect(screen, RED, downsize_button)
        pygame.draw.rect(screen, GREEN, upsize_button)
        pygame.draw.rect(screen, RED, downagent_button)
        pygame.draw.rect(screen, GREEN, upagent_button)
        pygame.draw.rect(screen, RED, downspeed_button)
        pygame.draw.rect(screen, GREEN, upspeed_button)
        screen.blit(start_text2, (150, 390))
        screen.blit(quit_text2, (150, 490))
        screen.blit(time_texte, (50, 170))
        screen.blit(size_texte,(50,220))
        screen.blit(nbA_texte,(50,270))
        screen.blit(speed_texte,(50,320))
        screen.blit(titre2, (60, 100))
    pygame.display.flip()
pygame.quit()
print("Temps écoulé. Fin du jeu.")
maxPoint=0
bestStudent = students[0]
for e in students:
    print(f"{e.nom} marque : {e.nbPoint} point(s) avec la stratégie {e.numStrat}")
    if(e.nbPoint>maxPoint):
        bestStudent = e
        maxPoint = e.nbPoint
print(f"Victoire de {bestStudent.nom} : La meilleure stratégie est la {bestStudent.numStrat}")
#"""
