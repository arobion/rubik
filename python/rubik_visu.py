import sys, pygame
from pygame.locals import *

POS_B = (0, 3)
POS_L = (3, 0)
POS_U = (3, 3)
POS_R = (3, 6)
POS_D = (3, 9)
POS_F = (6, 3)

class RubikVisu:
    """
    cube in pixel = 480px, 360px
    """
    #1 = yellow
    #2 = white
    #3 = blue
    #4 = green
    #5 = red
    #6 = orange

    def __init__(self, window):
        cube = []
        for i in range(9):
            cube.append([0] * 12)
        self.cube = cube
        self.img_u = pygame.image.load("./resource/cube_yellow.png").convert()
        self.img_d = pygame.image.load("./resource/cube_white.png").convert()
        self.img_f = pygame.image.load("./resource/cube_blue.png").convert()
        self.img_b = pygame.image.load("./resource/cube_green.png").convert()
        self.img_r = pygame.image.load("./resource/cube_red.png").convert()
        self.img_l = pygame.image.load("./resource/cube_orange.png").convert()
        self.face_u = [1] * 9
        self.face_d = [2] * 9
        self.face_f = [3] * 9
        self.face_b = [4] * 9
        self.face_r = [5] * 9
        self.face_l = [6] * 9
        self.put_face2cube(self.cube, self.face_u, POS_U)
        self.put_face2cube(self.cube, self.face_d, POS_D)
        self.put_face2cube(self.cube, self.face_f, POS_F)
        self.put_face2cube(self.cube, self.face_b, POS_B)
        self.put_face2cube(self.cube, self.face_r, POS_R)
        self.put_face2cube(self.cube, self.face_l, POS_L)

    def put_face2cube(self, cube, face, pos):
        x, y = pos
        for value in face:
            cube[x][y] = value
            x += 1
            if x % 3 == 0:
                x -= 3
                y += 1

    def put_cube2window(self, window):
        x = 2
        y = 3
        for row in self.cube:
            for value in row:
                if value != 0:
                    if value == 1:
                        window.blit(self.img_u, (x * 40, y * 40))
                    if value == 2:
                        window.blit(self.img_d, (x * 40, y * 40))
                    if value == 3:
                        window.blit(self.img_f, (x * 40, y * 40))
                    if value == 4:
                        window.blit(self.img_b, (x * 40, y * 40))
                    if value == 5:
                        window.blit(self.img_r, (x * 40, y * 40))
                    if value == 6:
                        window.blit(self.img_l, (x * 40, y * 40))
                x += 1
            y += 1 
            x = 2

pygame.init()

size = width, height = 800, 600

window = pygame.display.set_mode(size)

backgound = pygame.image.load("./resource/background.png").convert()

cube = RubikVisu(window)

for i in cube.cube:
    print(i)
    
while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
    window.blit(backgound, (0, 0))
    cube.put_cube2window(window)
    pygame.display.flip()
