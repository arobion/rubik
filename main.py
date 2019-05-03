from rubik_cubes import Rubik
from rubik_moves import move, move_by_notation
from rubik_state import rubik_state
from ida import IDA

def scramble(string, rubik):
    move_by_notation(rubik, string)


def main():
    rubik = Rubik()
    start = rubik_state(rubik, 0)

    scramble("U", rubik)
    scramble("R", rubik)
    print(rubik.heuristic(rubik))

    print(start)
    print(rubik.heuristic(start))

    ida = IDA(start, rubik.heuristic)
    print(ida.bound)
    print(ida.path)

if __name__ == "__main__":
    main()
