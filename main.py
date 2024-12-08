import itertools
from environnement import Environnement
from Player.agent import Agent
import time
import random
import pygame

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
pygame.display.set_caption("Jeu des narvalos")

def draw_board(couleur1=SOL, couleur2=SOL):
    """Dessine un sol avec des carreaux et des lignes noires.""" 
    board = pygame.Rect(0, 0, WIDTH, WIDTH)
    pygame.draw.rect(screen, SOL, board)    
    for row, col in itertools.product(range(TAILLE), range(TAILLE)): 
        pygame.draw.rect(screen, BLACK, (col * TAILLE_CASE, row * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE), 1)
def draw_board_1(couleur1=WHITE, couleur2=BLACK):
    """Dessine le damier."""
    for row, col in itertools.product(range(TAILLE), range(TAILLE)):
        color = couleur1 if (row + col) % 2 == 0 else couleur2
        pygame.draw.rect(screen, color, (col * TAILLE_CASE, row * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE))

class Img_Agent:
    def __init__(self,img,x,y):
        self.x=x
        self.y=y
        self.position = (self.x, self.y)
        self.img = pygame.image.load(f"img/skins/{img}.png")
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
        self.grid=Environnement(tailleGrid,[8,8])
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

#Définitions de student4
img_obstacle1=Img_Agent("obstacle",0,6)
obstacle1=Agent("O",0,6,taille,None,img_obstacle1.update_position)

students=[student1,student2,student3,student4]
obstacles=[obstacle1]

#Définitions de teacher
img_teacher=Img_Agent("teacher",(taille // 2)-1,(taille // 2))
teacher = Agent("I", (taille // 2)-1, (taille // 2), taille,None,img_teacher.update_position)

list_Img = [img_student1,img_student2,img_student3,img_student4,img_teacher,img_obstacle1]
font2=pygame.font.Font(None, 24)
font = pygame.font.Font(None, 74)
small_font = pygame.font.Font(None, 36)

main=Main(taille,students,teacher,obstacles)

candy_position = main.grid.candy
img_candy = pygame.image.load("img/skins/candy.png")
img_candy = pygame.transform.scale(img_candy, (TAILLE_CASE, TAILLE_CASE))

def draw_candy(x, y):
    screen.blit(img_candy, (x * TAILLE_CASE, y * TAILLE_CASE))

input_test = "ok"
x = 30
start_time = time.time()
#"""
running = True
titre = font.render("Menu Principal", True, WHITE)
start_text = small_font.render("Démarrer le jeu", True, WHITE)
quit_text = small_font.render("Quitter", True, WHITE)
start_button = pygame.Rect(60, 200, 380, 50)
quit_button = pygame.Rect(60, 300, 380, 50)
titre2 = font.render("Option", True, WHITE)
start_text2 = small_font.render("Démarrer le jeu", True, WHITE)
quit_text2 = small_font.render("Quitter", True, WHITE)
time_texte = small_font.render(f"Temps de jeux : {x}", True, WHITE)
size_texte = small_font.render(f"Taille du plateau : {str(taille)}", True, WHITE)
start_button2 = pygame.Rect(60, 380, 380, 50)
quit_button2 = pygame.Rect(60, 480, 380, 50)
downtime_button = pygame.Rect(300, 170, 25, 25)
uptime_button = pygame.Rect(350, 170, 25, 25)
downsize_button = pygame.Rect(300, 220, 25, 25)
upsize_button = pygame.Rect(350, 220, 25, 25)
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
                    state = "game"
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
    if state == "game":
        elapsed_time = time.time() - start_time
        if elapsed_time > x:
            running = False
        draw_board()
        draw_candy(*candy_position)
        for e in list_Img:
            e.draw()
        img_teacher.draw()
        main.grid.afficher()
        main.updateAgents()
        text1 = font2.render(main.grid.msg,1,(255,255,255))
        text2 = font2.render(f"{int(elapsed_time)} / {str(x)}s", 1, (255, 255, 255))
        screen.blit(text1, (10, 510))
        screen.blit(text2, (10, 530))
        time.sleep(0.3)
    elif state == "menu":
        pygame.draw.rect(screen, BLUE, start_button)
        pygame.draw.rect(screen, RED, quit_button)
        screen.blit(start_text, (150, 210))
        screen.blit(quit_text, (150, 310))
        screen.blit(titre, (60, 100))
    elif state == "option":
        pygame.draw.rect(screen, BLUE, start_button2)
        pygame.draw.rect(screen, RED, quit_button2)
        pygame.draw.rect(screen, RED, downtime_button)
        pygame.draw.rect(screen, GREEN, uptime_button)
        pygame.draw.rect(screen, RED, downsize_button)
        pygame.draw.rect(screen, GREEN, upsize_button)
        screen.blit(start_text2, (150, 390))
        screen.blit(quit_text2, (150, 490))
        screen.blit(time_texte, (50, 170))
        screen.blit(size_texte,(50,220))
        screen.blit(titre2, (60, 100))
    pygame.display.flip()
pygame.quit()
print("Temps écoulé. Fin du jeu.")
maxPoint=0
bestStudent = student1
for e in students:
    print(f"{e.nom} marque : {e.nbPoint} point(s) avec la stratégie {e.numStrat}")
    if(e.nbPoint>maxPoint):
        bestStudent = e
        maxPoint = e.nbPoint
print(f"Victoire de {bestStudent.nom} : La meilleure stratégie est la {bestStudent.numStrat}")
#"""
