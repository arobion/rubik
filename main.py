import argparse

from rubik_cubes import Rubik
from rubik_moves import move, move_by_notation
from rubik_state import rubik_state

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
    print(rubik)

if __name__ == "__main__":
    main()
