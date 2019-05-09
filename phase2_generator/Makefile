CC = g++
CFLAG = -Wall -Wextra -Werror --std=c++14

NAME = phase2_generator

FILE =  main.cpp \
		Instruction.cpp \
		State.cpp \
		move.cpp

all:
	$(CC) $(CFLAG) $(FILE) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean