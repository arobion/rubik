from rubik_cubes import Rubik
from rubik_moves import move

def main():
    rubik = Rubik()
    move(rubik, 1)
    print(rubik)

if __name__ == "__main__":
    main()
