##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Elias Josué HAJJAR LLAUQUEN
##

NAME = 42sh

CPPFLAGS = -I./include

#CFLAGS = -W -Wall -Wextra -Werror

CFLAGS = -g3

SRC =	src/mysh.c				\
		src/separate_args.c		\
		src/command.c			\
		src/env.c				\
		src/struct.c			\
		lib/mini_printf.c		\
		lib/my_strncpy.c		\
		lib/my_strcmp.c			\
		lib/my_strdup.c			\
		lib/my_strncmp.c		\
		lib/my_strskipcpy.c		\
		lib/my_strcat.c			\
		lib/alphanumeric.c		\
		lib/list_chaine_input.c		\
		src/parsings_seperator.c

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
