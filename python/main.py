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

def convert_list2str(l):
    res = ""
    for s in l:
        res += s
        res += " "
    res = res.strip()
    return res

def launch_visu(cpp):
    pg.init()
    size = width, height = 1200, 600
    window = pg.display.set_mode(size)
    backgound = pg.image.load("./resource/background.png").convert()
    kociemba = pg.image.load("./resource/kociemba.jpg").convert()
    cube = RubikVisu(window)
    input_box = InputBox(650, 140, 400, 32)
    
    font_title = pg.font.Font("./resource/04B_30__.TTF", 50)
    font = pg.font.Font("./resource/04B_30__.TTF", 20)
    font_result = pg.font.Font(None, 25)
    title = font_title.render("MEGA Rubik's solver 3000", True, (255, 0, 0))
    text_to_solve = font.render("Press S to solve", True, (0, 0, 0))
    text_to_reset = font.render("Press X to reset", True, (0, 0, 0))
    text_to_input = font.render("Enter number or scramble", True, (0, 0, 0))
    text_to_skynet = font.render("Skynet confirmed !", True, (255, 0, 0))
    text_to_solution_put = font.render("Currently:  (press key left or right)", True, (0, 0, 0))
    
    text = ""
    flag_scrambled = False
    solution = []
    solution_put = []
    melange = ""
    while 1:
        window.fill((30, 30, 30))
        window.blit(backgound, (0, 0))
        window.blit(kociemba, (700, 240))
        window.blit(title, (100, 50))
        window.blit(text_to_input, (650, 110))
        window.blit(text_to_solve, (650, 180))
        window.blit(text_to_reset, (650, 210))
        cube.put_cube2window(window)
        if len(melange):
            if len(melange) <= 50:
                text_to_scramble = font.render("Scramble: (moves: " + str(len(melange.split())) + ")", True, (0, 0, 0))
                text_scramble = font_result.render(melange, True, (0, 0, 0))
                window.blit(text_scramble, (400, 430))
            if len(melange) > 50:
                text_to_scramble = font.render("Scramble too large to be displayed", True, (0, 0, 0))
            window.blit(text_to_scramble, (400, 400))
        if len(solution):
            text_to_solution = font.render("Solution: (moves: " + str(len(solution)) + ")", True, (0, 0, 0))
            window.blit(text_to_solution, (400, 460))
            text_solution = font_result.render(convert_list2str(solution), True, (0, 0, 0))
            window.blit(text_solution, (400, 480))
            window.blit(text_to_skynet, (720, 290))
        if len(solution_put):
            window.blit(text_to_solution_put, (400, 510))
            text_solution_put = font_result.render(convert_list2str(solution_put), True, (0, 0, 0))
            window.blit(text_solution_put, (400, 540))

        for event in pg.event.get():
            if event.type == pg.QUIT:
                cpp.kill()
                sys.exit()
            else:
                if event.type == pg.KEYDOWN:
                    if event.key == pg.K_s:
                        if flag_scrambled == True:
                            flag_scrambled = False
                            solution = handle_cpp(cpp, rubik, melange).split()
                            solution_put = solution
                            cube.scramble(convert_list2str(solution))
                            cube.put_cube2window(window)
                    if event.key == pg.K_x:
                        solution = []
                        solution_put = []
                        melange = ""
                        cube.reset_visu()
                        cube.put_cube2window(window)
                    if event.key == pg.K_RIGHT and len(solution):
                        if len(solution_put) != len(solution):
                            solution_put = solution[:len(solution_put) + 1]
                            cube.reset_visu()
                            cube.scramble(melange)
                            cube.scramble(convert_list2str(solution_put))
                            cube.put_cube2window(window)
                    if event.key == pg.K_LEFT and len(solution):
                        if len(solution_put) != 0:
                            solution_put = solution[:len(solution_put) - 1]
                            cube.reset_visu()
                            cube.scramble(melange)
                            cube.scramble(convert_list2str(solution_put))
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
                        solution = []
                        solution_put = []
                    except Exception as e:
                        print("entrer un melange valide")
                    melange = text
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
