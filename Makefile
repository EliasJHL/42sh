##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Elias Josué HAJJAR LLAUQUEN
##

NAME = 42sh

CPPFLAGS = -I./include

#CFLAGS = -W -Wall -Wextra -Werror

SRC =	src/mysh.c				\
		src/separate_args.c		\
		src/command.c			\
		src/env.c				\
		src/struct.c			\
		src/prompt_display.c	\
		src/history.c			\
		src/history_handle.c	\
		src/globbing.c			\
		lib/mini_printf.c		\
		lib/my_strncpy.c		\
		lib/my_strcmp.c			\
		lib/my_strdup.c			\
		lib/my_strncmp.c		\
		lib/my_strskipcpy.c		\
		lib/my_strcat.c			\
		lib/alphanumeric.c		\
		lib/my_getnbr.c

OBJ = $(SRC:.c=.o)

LOGO	=	echo "                                                                                                                        ";	\
			echo " ___   ___    _______  ________  ___  ___          _______   ________  ___  _________  _______   ________  ___  ___     ";	\
            echo "|\\  \\ |\\  \\  /  ___  \\|\\   ____\\|\\  \\|\\  \\        |\\  ___ \\ |\\   __  \\|\\  \\|\\___   ___\\\\  ___ \\ |\\   ____\\\\ |\\\\  \\    \\ ";	\
            echo "\\ \\  \\__\\  \\/__/|_/  /\\ \\  \\___|\\ \\  \\\_\\\  \\       \\ \\   __/|\\ \\  \\|\\  \\ \\  \\|___ \\  \\_\\ \\   __/|\\ \\  \\___|\\ \\  \\\_\\\  \\   ";	\
            echo " \\ \\______  \\__|//  / /\\ \\_____  \\ \\   __  \\       \\ \\  \\_|/_\\ \\   ____\\ \\  \\   \\ \\  \\ \\ \\  \\_|/_\\ \\  \\    \\ \\   __  \\  ";	\
            echo "  \\|_____|\\  \\  /  /_/__\\|____|\\  \\ \\  \\ \\  \\       \\ \\  \\_|\\ \\ \\  \\___|\\ \\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\ \\  \\ ";	\
            echo "         \\ \\__\\|\\________\\____\\_\\  \\ \\__\\ \\__\\       \\ \\_______\\ \\__\\    \\ \\__\\   \\ \\__\\ \\ \\_______\\ \\_______\\ \\__\\ \\__\\";	\
            echo "          \\|__| \\|_______|\\_________\\|__|\\|__|        \\|_______|\\|__|     \\|__|    \\|__|  \\|_______|\\|_______|\\|__|\\|__|";	\
            echo "                         \\|_________|                                                                                   ";	\
            echo "                                                                                                                        ";	\
            echo "                                                                                  By Elias, Brahim, Pierrik, Enzo, Sarah";	\
            echo "                                                                                                                        ";	\

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	@$(LOGO)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:	clean
