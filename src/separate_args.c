/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

void separate_command(char *arg, history_t *history)
{
    char *ptr;
    char *token = strtok_r(arg, ";", &ptr);

    while (token != NULL) {
        command(token, history);
        token = strtok_r(NULL, ";", &ptr);
    }
}

void separate_arg(char *arg)
{
    int i = 0;
    int nbword = 0;
    char *temp = my_strdup(arg);
    char *ptr;
    char *token = strtok_r(temp, " \t\n", &ptr);

    while (token != NULL){
        nbword += 1;
        token = strtok_r(NULL, " \t\n", &ptr);
    }
    free(temp);
    data()->nb_args = nbword - 1;
    data()->array = malloc((nbword + 1) * sizeof(char *));
    token = strtok_r(arg, " \t\n", &ptr);
    while (token != NULL) {
        data()->array[i] = my_strdup(token);
        token = strtok_r(NULL, " \t\n", &ptr);
        i++;
    }
    data()->array[i] = NULL;
}
