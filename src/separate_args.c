/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static int copy_pipe(int i, int j)
{
    int k = i;
    int l = 0;
    int nb_arg = 0;

    while (data()->array[k + 1] != NULL && COMPARR(k + 1, "|") != 0) {
        nb_arg++;
        k++;
    }
    data()->pipe[j] = malloc((nb_arg + 1) * sizeof(char *));
    while (data()->array[i + 1] != NULL && COMPARR(i + 1, "|") != 0) {
        data()->pipe[j][l] = my_strdup(data()->array[i + 1]);
        i++;
        l++;
    }
    data()->pipe[j][l] = NULL;
    return i;
}

static void remove_pipe(void)
{
    int j = 0;

    for (int i = 0; data()->array[i] != NULL; i++){
        if (COMPARR(i, "|") == 0){
            free(data()->array[i]);
            data()->array[i] = NULL;
            j = i + 1;
            break;
        }
    }
    if (j != 0){
        while (data()->array[j] != NULL){
            free(data()->array[j]);
            j++;
        }
    }
}

void separate_pipe(void)
{
    int i = 0;
    int j = 0;

    data()->nb_pipe = 0;
    for (int i = 0; data()->array[i] != NULL; i++)
        if (COMPARR(i, "|") == 0 && data()->array[i + 1] != NULL)
            data()->nb_pipe += 1;
    data()->pipe = malloc((data()->nb_pipe + 1) * sizeof(char **));
    while (data()->array[i] != NULL && j < data()->nb_pipe){
        if (COMPARR(i, "|") == 0){
            i = copy_pipe(i, j);
            j++;
        }
        i++;
    }
    data()->pipe[j] = NULL;
    remove_pipe();
}

void separate_command(char *arg)
{
    char *ptr;
    char *token = strtok_r(arg, ";", &ptr);

    while (token != NULL) {
        command(token);
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
