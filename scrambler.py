import argparse
import random


def gen_scramble(set_moves, size):
    ret = "\""
    for i in range(size):
        ret += random.choice(set_moves) + " "
    print(ret[:-1] + "\"")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("nb_moves", type=int, help="specify the len of the scrambling")
    parser.add_argument("-g1", "--state_g1", action="store_true", help="scramble only in a G1 state")
    args = parser.parse_args()

    set_moves = ["U", "D", "U'", "D'", "U2", "D2", "R2", "L2", "F2", "B2"]
    if args.state_g1 == False:
        set_moves.append("R")
        set_moves.append("R'")
        set_moves.append("L")
        set_moves.append("L'")
        set_moves.append("F")
        set_moves.append("F'")
        set_moves.append("B")
        set_moves.append("B'")

    gen_scramble(set_moves, args.nb_moves)

if __name__ == "__main__":
    main()
