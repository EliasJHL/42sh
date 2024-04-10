##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Elias Josué HAJJAR LLAUQUEN
##

NAME = 42sh

CPPFLAGS = -I./include

SRC = 	main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:	clean
