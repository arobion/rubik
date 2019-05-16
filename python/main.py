import argparse
import random
import time
import subprocess

from rubik_cubes import Rubik
from rubik_moves import move, move_by_notation, move_translator
from rubik_state import rubik_state
from rubik_next import get_nexts_1, get_nexts_2
from rubik_ida import IDA

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
            raise Exception("Error unvalid move : {}, look at usage for more information".format(elem))
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


def main():
#    parser = argparse.ArgumentParser()
#    parser.add_argument("scramble", help="Please enter a scramble composed of following moves :<U, U', U2, R, R', R2, L, L', L2, D, D', D2, F, F', F2, B, B', B2> ")
#    args = parser.parse_args()
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
    cpp.kill()

if __name__ == "__main__":
    main()
