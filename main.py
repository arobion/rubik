from rubik_cubes import Rubik
from rubik_moves import move
from rubik_state import rubik_state

def main():
    rubik = Rubik()
#    move(rubik, 1)
#    print(rubik)
    stat = rubik_state(rubik, 0)
    print(stat)
    stat2 = rubik_state(stat, 1)
    print(stat2.state)

if __name__ == "__main__":
    main()
