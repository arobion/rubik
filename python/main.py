import argparse
import time
import subprocess

from rubik_cubes import Rubik
from rubik_moves import move, move_by_notation, move_translator
from rubik_state import rubik_state
from rubik_next import get_nexts_1, get_nexts_2
from rubik_ida import IDA

def scramble(string, rubik):
    valid_moves = ["U", "U'", "U2", "R", "R'", "R2", "L", "L'", "L2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"]
    moves = string.split()
    for elem in moves:
        if elem not in valid_moves:
            raise Exception("Error unvalid move : {}, look at usage for more information".format(elem))
        move_by_notation(rubik, elem)

def handle_cpp(cpp, rubik):
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
    solution = cpp.stdout.readline()
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
    print("Please enter a scramble :")
    instruction = input()
    while instruction != "exit":
        try:
            rubik = Rubik()
            scramble(instruction, rubik)
            handle_cpp(cpp, rubik)
        except Exception as e:
            print(e)
        print("Please enter a scramble :")
        instruction = input()

if __name__ == "__main__":
    main()
