import argparse
import random
import subprocess
import sys
import time

import pygame as pg
from pygame.locals import *

from rubik_cubes import Rubik
from rubik_moves import move, move_by_notation, move_translator
from rubik_visu import *
#from rubik_state import rubik_state
#from rubik_next import get_nexts_1, get_nexts_2
#from rubik_ida import IDA


def random_scramble(number):
    ret = ""
    set_moves = ["U", "D", "R", "L", "F", "B", "U'", "D'", "R'", "L'", "F'", "B'", "U2", "D2", "R2", "L2", "F2", "B2"]
    last_move = "E"
    for i in range(number):
        move = random.choice(set_moves)
        while(move[0] == last_move[0]):
            move = random.choice(set_moves)
        ret += move + " "
        last_move = move
    return ret[:-1]


def scramble(string, rubik):
    valid_moves = ["U", "U'", "U2", "R", "R'", "R2", "L", "L'", "L2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"]
    moves = string.split()
    for elem in moves:
        if elem not in valid_moves:
            raise Exception("Error unvalid move : {}".format(elem))
        move_by_notation(rubik, elem)

def handle_cpp(cpp, rubik, instructions):
    corners = ""
    for i in range(1, 9):
        corners += str(rubik.corners[i].final_position - 1) + " "
    edges = ""
    for i in range(1, 13):
        edges += str(rubik.edges[i].final_position - 1) + " "
    co = ""
    for i in range(1, 9):
        co += str(rubik.corners[i].orientation) + " "
    eo = ""
    for i in range(1, 13):
        eo += str(rubik.edges[i].orientation) + " "

    cpp.stdin.write("{}{}{}{}\n".format(corners, edges, co, eo))
    start_time = time.time()
    solution = cpp.stdout.readline()
    print("\nscramble: {}".format(instructions))
    print("time resolution: {:.2f} s".format(time.time() - start_time))
    print("nb moves: {}".format(len(solution.split())))
    print("solution: {}".format(solution), end="")
    return solution

def launch_cmd(cpp):
    print("\nPlease enter a specific scramble or a size for a random scramble:")
    instruction = input()
    while instruction != "exit":
        rubik = Rubik()
        try:
            number = int(instruction)
            instruction = random_scramble(number)
        except Exception as e:
            pass
        try:
            scramble(instruction, rubik)
            handle_cpp(cpp, rubik, instruction)
        except Exception as e:
            print(e)
        print("\nPlease enter a specific scramble or a size for a random scramble:")
        instruction = input()
    print("Bye")
    cpp.kill()

def launch_visu(cpp):
    pg.init()
    size = width, height = 1200, 600
    window = pg.display.set_mode(size)
    backgound = pg.image.load("./resource/background.png").convert()
    cube = RubikVisu(window)
    input_box = InputBox(650, 240, 400, 32)
    
    font_title = pg.font.Font("./resource/04B_30__.TTF", 50)
    font = pg.font.Font("./resource/04B_30__.TTF", 20)
    title = font_title.render("MEGA Rubik's solver 3000", True, (255, 0, 0))
    text_to_solve = font.render("Press S to solve", True, (0, 0, 0))
    text_to_reset = font.render("Press X to reset", True, (0, 0, 0))
    text_to_input = font.render("Enter number or scramble", True, (0, 0, 0))
    
    text = ""
    flag_scrambled = False
    solution = []
    while 1:
        window.fill((30, 30, 30))
        window.blit(backgound, (0, 0))
        window.blit(title, (100, 50))
        window.blit(text_to_solve, (650, 160))
        window.blit(text_to_reset, (650, 190))
        window.blit(text_to_input, (650, 220))
        cube.put_cube2window(window)
        if len(solution):
            cube.make_move(solution.pop(0))
            cube.put_cube2window(window)
        else:
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    cpp.kill()
                    sys.exit()
                else:
                    if event.type == pg.KEYDOWN:
                        if event.key == pg.K_s:
                            print(flag_scrambled)
                            if flag_scrambled == True:
                                flag_scrambled = False
                                solution = handle_cpp(cpp, rubik, cube.melange).split()
                        if event.key == pg.K_x:
                            cube.reset_visu()
                            cube.put_cube2window(window)
                    text = input_box.handle_event(event)
                    if text != "":
                        rubik = Rubik()
                        cube.reset_visu()
                        try:
                            number = int(text)
                            text = random_scramble(number)
                        except Exception as e:
                            pass
                        try:
                            scramble(text, rubik)
                            cube.scramble(text)
                        except Exception as e:
                            print("entrer un melange valide")
                        cube.melange = text
                        text = ""
                        cube.put_cube2window(window)
                        flag_scrambled = True
        input_box.update()
        input_box.draw(window)
        pg.display.flip()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--visu", help="Display window", action="store_true")
    args = parser.parse_args()

    print("Loading C++ program :")
    subprocess.run(["make -C ../cpp/."], shell=True, stdout=subprocess.PIPE)
    print('\tcompilation Done')
    cpp = subprocess.Popen(["../cpp/rubik"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, bufsize=1, universal_newlines=True)
    cpp.stdout.flush()
    read = cpp.stdout.readline()
    while read != "Ready\n":
        print("\t" + read, end="")
        read = cpp.stdout.readline()
    print("C++ program is Ready")
    if args.visu:
        launch_visu(cpp)
    else:
        launch_cmd(cpp)

if __name__ == "__main__":
    main()
