/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main.c
*/

#include "include/shell.h"

int comp(char buffer, char *delim, int i)
{
    static int rest = 0;
    if (buffer[i] == '\"')
        return 0;
    for (int l = 0; delim[l] != '\0'; l++) {
        if (delim[l] == buffer[i])
            return 1;
    }
    return 0;
}

int number_word(char *buffer)
{
    char *delim = " \n\t";
    int nb_compt = 0;
    int i = 0;

    while (buffer[i] != '\0') {
        if (!comp(buffer[i], delim))
            nb_compt++;
        i++;
    }
    return nb_compt;
}

char **cut_arg(char *buffer)
{
    int nbword = number_word(buffer);
    char **array = malloc((nbword + 1) * sizeof(char *));


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