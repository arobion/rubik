import sys, pygame
from pygame.locals import *

POS_B = (3,0)
POS_L = (0,3)
POS_U = (3,3)
POS_R = (6,3)
POS_D = (9,3)
POS_F = (3,6)

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

    def put_face2cube(self, cube, face, pos):
        x, y = pos
        for value in face:
            cube[y][x] = value
            x += 1
            if x % 3 == 0:
                x -= 3
                y += 1

    def put_cube2window(self, window):
        self.put_face2cube(self.cube, self.face_u, POS_U)
        self.put_face2cube(self.cube, self.face_d, POS_D)
        self.put_face2cube(self.cube, self.face_f, POS_F)
        self.put_face2cube(self.cube, self.face_b, POS_B)
        self.put_face2cube(self.cube, self.face_r, POS_R)
        self.put_face2cube(self.cube, self.face_l, POS_L)
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

    def make_move(self, move):
        if move == "U'":
            tmp = [self.face_f[0], self.face_f[1], self.face_f[2]]
            self.face_f[0], self.face_f[1], self.face_f[2] = self.face_l[2], self.face_l[5], self.face_l[8]
            self.face_l[2], self.face_l[5], self.face_l[8] = self.face_b[8], self.face_b[7], self.face_b[6]
            self.face_b[8], self.face_b[7], self.face_b[6] = self.face_r[6], self.face_r[3], self.face_r[0]
            self.face_r[6], self.face_r[3], self.face_r[0] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_u[0]
            self.face_u[0] = self.face_u[2]
            self.face_u[2] = self.face_u[8]
            self.face_u[8] = self.face_u[6]
            self.face_u[6] = tmp
            tmp = self.face_u[1]
            self.face_u[1] = self.face_u[5]
            self.face_u[5] = self.face_u[7]
            self.face_u[7] = self.face_u[3]
            self.face_u[3] = tmp
        
        if move == "U":
            tmp = [self.face_f[0], self.face_f[1], self.face_f[2]]
            self.face_f[0], self.face_f[1], self.face_f[2] = self.face_r[6], self.face_r[3], self.face_r[0]
            self.face_r[6], self.face_r[3], self.face_r[0] = self.face_b[8], self.face_b[7], self.face_b[6]
            self.face_b[8], self.face_b[7], self.face_b[6] = self.face_l[2], self.face_l[5], self.face_l[8]
            self.face_l[2], self.face_l[5], self.face_l[8] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_u[0]
            self.face_u[0] = self.face_u[6]
            self.face_u[6] = self.face_u[8]
            self.face_u[8] = self.face_u[2]
            self.face_u[2] = tmp
            tmp = self.face_u[1]
            self.face_u[1] = self.face_u[3]
            self.face_u[3] = self.face_u[7]
            self.face_u[7] = self.face_u[5]
            self.face_u[5] = tmp
        
        if move == "D":
            tmp = [self.face_f[6], self.face_f[7], self.face_f[8]]
            self.face_f[6], self.face_f[7], self.face_f[8] = self.face_l[0], self.face_l[3], self.face_l[6]
            self.face_l[0], self.face_l[3], self.face_l[6] = self.face_b[2], self.face_b[1], self.face_b[0]
            self.face_b[2], self.face_b[1], self.face_b[0] = self.face_r[8], self.face_r[5], self.face_r[2]
            self.face_r[8], self.face_r[5], self.face_r[2] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_d[0]
            self.face_d[0] = self.face_d[2]
            self.face_d[2] = self.face_d[8]
            self.face_d[8] = self.face_d[6]
            self.face_d[6] = tmp
            tmp = self.face_d[1]
            self.face_d[1] = self.face_d[5]
            self.face_d[5] = self.face_d[7]
            self.face_d[7] = self.face_d[3]
            self.face_d[3] = tmp

        if move == "D'":
            tmp = [self.face_f[6], self.face_f[7], self.face_f[8]]
            self.face_f[6], self.face_f[7], self.face_f[8] = self.face_r[8], self.face_r[5], self.face_r[2]
            self.face_r[8], self.face_r[5], self.face_r[2] = self.face_b[2], self.face_b[1], self.face_b[0]
            self.face_b[2], self.face_b[1], self.face_b[0] = self.face_l[0], self.face_l[3], self.face_l[6]
            self.face_l[0], self.face_l[3], self.face_l[6] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_d[0]
            self.face_d[0] = self.face_d[6]
            self.face_d[6] = self.face_d[8]
            self.face_d[8] = self.face_d[2]
            self.face_d[2] = tmp
            tmp = self.face_d[1]
            self.face_d[1] = self.face_d[3]
            self.face_d[3] = self.face_d[7]
            self.face_d[7] = self.face_d[5]
            self.face_d[5] = tmp
        
        if move == "R":
            tmp = [self.face_f[2], self.face_f[5], self.face_f[8]]
            self.face_f[2], self.face_f[5], self.face_f[8] = self.face_d[8], self.face_d[5], self.face_d[2]
            self.face_d[8], self.face_d[5], self.face_d[2] = self.face_b[2], self.face_b[5], self.face_b[8]
            self.face_b[2], self.face_b[5], self.face_b[8] = self.face_u[2], self.face_u[5], self.face_u[8]
            self.face_u[2], self.face_u[5], self.face_u[8] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_r[0]
            self.face_r[0] = self.face_r[6]
            self.face_r[6] = self.face_r[8]
            self.face_r[8] = self.face_r[2]
            self.face_r[2] = tmp
            tmp = self.face_r[1]
            self.face_r[1] = self.face_r[3]
            self.face_r[3] = self.face_r[7]
            self.face_r[7] = self.face_r[5]
            self.face_r[5] = tmp
        
        if move == "R'":
            tmp = [self.face_f[2], self.face_f[5], self.face_f[8]]
            self.face_f[2], self.face_f[5], self.face_f[8] = self.face_u[2], self.face_u[5], self.face_u[8]
            self.face_u[2], self.face_u[5], self.face_u[8] = self.face_b[2], self.face_b[5], self.face_b[8]
            self.face_b[2], self.face_b[5], self.face_b[8] = self.face_d[8], self.face_d[5], self.face_d[2]
            self.face_d[8], self.face_d[5], self.face_d[2] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_r[0]
            self.face_r[0] = self.face_r[2]
            self.face_r[2] = self.face_r[8]
            self.face_r[8] = self.face_r[6]
            self.face_r[6] = tmp
            tmp = self.face_r[1]
            self.face_r[1] = self.face_r[5]
            self.face_r[5] = self.face_r[7]
            self.face_r[7] = self.face_r[3]
            self.face_r[3] = tmp
        
        if move == "L'":
            tmp = [self.face_f[0], self.face_f[3], self.face_f[6]]
            self.face_f[0], self.face_f[3], self.face_f[6] = self.face_d[6], self.face_d[3], self.face_d[0]
            self.face_d[6], self.face_d[3], self.face_d[0] = self.face_b[0], self.face_b[3], self.face_b[6]
            self.face_b[0], self.face_b[3], self.face_b[6] = self.face_u[0], self.face_u[3], self.face_u[6]
            self.face_u[0], self.face_u[3], self.face_u[6] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_l[0]
            self.face_l[0] = self.face_l[2]
            self.face_l[2] = self.face_l[8]
            self.face_l[8] = self.face_l[6]
            self.face_l[6] = tmp
            tmp = self.face_l[1]
            self.face_l[1] = self.face_l[5]
            self.face_l[5] = self.face_l[7]
            self.face_l[7] = self.face_l[3]
            self.face_l[3] = tmp

        if move == "L":
            tmp = [self.face_f[0], self.face_f[3], self.face_f[6]]
            self.face_f[0], self.face_f[3], self.face_f[6] = self.face_u[0], self.face_u[3], self.face_u[6]
            self.face_u[0], self.face_u[3], self.face_u[6] = self.face_b[0], self.face_b[3], self.face_b[6]
            self.face_b[0], self.face_b[3], self.face_b[6] = self.face_d[6], self.face_d[3], self.face_d[0]
            self.face_d[6], self.face_d[3], self.face_d[0] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_l[0]
            self.face_l[0] = self.face_l[6]
            self.face_l[6] = self.face_l[8]
            self.face_l[8] = self.face_l[2]
            self.face_l[2] = tmp
            tmp = self.face_l[1]
            self.face_l[1] = self.face_l[3]
            self.face_l[3] = self.face_l[7]
            self.face_l[7] = self.face_l[5]
            self.face_l[5] = tmp
        
        if move == "F":
            tmp = [self.face_u[6], self.face_u[7], self.face_u[8]]
            self.face_u[6], self.face_u[7], self.face_u[8] = self.face_l[6], self.face_l[7], self.face_l[8]
            self.face_l[6], self.face_l[7], self.face_l[8] = self.face_d[8], self.face_d[7], self.face_d[6]
            self.face_d[8], self.face_d[7], self.face_d[6] = self.face_r[6], self.face_r[7], self.face_r[8]
            self.face_r[6], self.face_r[7], self.face_r[8] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_f[0]
            self.face_f[0] = self.face_f[6]
            self.face_f[6] = self.face_f[8]
            self.face_f[8] = self.face_f[2]
            self.face_f[2] = tmp
            tmp = self.face_f[1]
            self.face_f[1] = self.face_f[3]
            self.face_f[3] = self.face_f[7]
            self.face_f[7] = self.face_f[5]
            self.face_f[5] = tmp
        
        if move == "F'":
            tmp = [self.face_u[6], self.face_u[7], self.face_u[8]]
            self.face_u[6], self.face_u[7], self.face_u[8] = self.face_r[6], self.face_r[7], self.face_r[8]
            self.face_r[6], self.face_r[7], self.face_r[8] = self.face_d[8], self.face_d[7], self.face_d[6]
            self.face_d[8], self.face_d[7], self.face_d[6] = self.face_l[6], self.face_l[7], self.face_l[8]
            self.face_l[6], self.face_l[7], self.face_l[8] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_f[0]
            self.face_f[0] = self.face_f[2]
            self.face_f[2] = self.face_f[8]
            self.face_f[8] = self.face_f[6]
            self.face_f[6] = tmp
            tmp = self.face_f[1]
            self.face_f[1] = self.face_f[5]
            self.face_f[5] = self.face_f[7]
            self.face_f[7] = self.face_f[3]
            self.face_f[3] = tmp

        if move == "B'":
            tmp = [self.face_u[0], self.face_u[1], self.face_u[2]]
            self.face_u[0], self.face_u[1], self.face_u[2] = self.face_l[0], self.face_l[1], self.face_l[2]
            self.face_l[0], self.face_l[1], self.face_l[2] = self.face_d[2], self.face_d[1], self.face_d[0]
            self.face_d[2], self.face_d[1], self.face_d[0] = self.face_r[0], self.face_r[1], self.face_r[2]
            self.face_r[0], self.face_r[1], self.face_r[2] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_b[0]
            self.face_b[0] = self.face_b[2]
            self.face_b[2] = self.face_b[8]
            self.face_b[8] = self.face_b[6]
            self.face_b[6] = tmp
            tmp = self.face_b[1]
            self.face_b[1] = self.face_b[5]
            self.face_b[5] = self.face_b[7]
            self.face_b[7] = self.face_b[3]
            self.face_b[3] = tmp
        
        if move == "B":
            tmp = [self.face_u[0], self.face_u[1], self.face_u[2]]
            self.face_u[0], self.face_u[1], self.face_u[2] = self.face_r[0], self.face_r[1], self.face_r[2]
            self.face_r[0], self.face_r[1], self.face_r[2] = self.face_d[2], self.face_d[1], self.face_d[0]
            self.face_d[2], self.face_d[1], self.face_d[0] = self.face_l[0], self.face_l[1], self.face_l[2]
            self.face_l[0], self.face_l[1], self.face_l[2] = tmp[0], tmp[1], tmp[2]
            tmp = self.face_b[0]
            self.face_b[0] = self.face_b[6]
            self.face_b[6] = self.face_b[8]
            self.face_b[8] = self.face_b[2]
            self.face_b[2] = tmp
            tmp = self.face_b[1]
            self.face_b[1] = self.face_b[3]
            self.face_b[3] = self.face_b[7]
            self.face_b[7] = self.face_b[5]
            self.face_b[5] = tmp

        if move == "B2":
            self.make_move("B")
            self.make_move("B")
        if move == "F2":
            self.make_move("F")
            self.make_move("F")
        if move == "U2":
            self.make_move("U")
            self.make_move("U")
        if move == "D2":
            self.make_move("D")
            self.make_move("D")
        if move == "R2":
            self.make_move("R")
            self.make_move("R")
        if move == "L2":
            self.make_move("L")
            self.make_move("L")

pygame.init()

size = width, height = 800, 600

window = pygame.display.set_mode(size)

backgound = pygame.image.load("./resource/background.png").convert()

cube = RubikVisu(window)
cube.make_move("L")
cube.make_move("U'")
cube.make_move("R")
cube.make_move("U'")
cube.make_move("U'")
cube.make_move("L'")
cube.make_move("R'")
cube.make_move("D'")
cube.make_move("R")
cube.make_move("L")
cube.make_move("D")
cube.make_move("F'")
cube.make_move("B")
cube.make_move("B2")




    
while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
    window.blit(backgound, (0, 0))
    cube.put_cube2window(window)
    pygame.display.flip()
