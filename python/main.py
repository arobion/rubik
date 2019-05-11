import argparse
import time

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


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("scramble", help="Please enter a scramble composed of following moves :<U, U', U2, R, R', R2, L, L', L2, D, D', D2, F, F', F2, B, B', B2> ")
    args = parser.parse_args()
    rubik = Rubik()
    try:
        scramble(args.scramble, rubik)
    except Exception as e:
        print(e)
        return

    phase1 = rubik_state(rubik, 0, rubik.heuristic_h1)
    ida1 = IDA(phase1, rubik.heuristic_h1, get_nexts_1, {}) # empty pruning table
    ret1 = ida1.run()

    total_moves = ""
    print("***** Phase 1 *****\n")
    for state in ret1:
        print(state)
        print("_______________________________________")
        if state.instruction != 0:
            total_moves += move_translator[state.instruction] + " "

    phase2 = rubik_state(ret1[-1], 0, rubik.heuristic_h2)
    ida2 = IDA(phase2, rubik.heuristic_h2, get_nexts_2, rubik.pruning_phase2)
    ret2 = ida2.run()

    print("\n***** Phase 2 *****\n")
    for state in ret2:
        print(state)
        print("_______________________________________")
        if state.instruction != 0:
            total_moves += move_translator[state.instruction] + " "

    print("scramble: {}".format(args.scramble))
    print("solution: {}".format(total_moves[:-1]))
    print(len(ret1) + len(ret2) - 2)


if __name__ == "__main__":
    main()
