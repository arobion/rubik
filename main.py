from rubik_cubes import Rubik
from rubik_moves import move, move_by_notation
from rubik_state import rubik_state

def scramble(string, rubik):
    move_by_notation(rubik, string)


def main():
    rubik = Rubik()
    scramble("U", rubik)
    print(rubik)

if __name__ == "__main__":
    main()
