/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main.c
*/

#include "include/shell.h"

int number_word(char *buffer)
{
    char *delim = " \n\t";


}

char **cut_arg(char *buffer)
{
    int nbword = number_word(buffer);
}

int main(int ac, char **av)
{
    char *buffer = NULL;
    size_t len = 0;
    int verif = 0;

    while (1) {
        printf("$> ");
        verif = getline(&buffer, &len, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(buffer, "exit") == 0)
            break;
    }
    return 0;
}