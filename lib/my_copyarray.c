/*
** EPITECH PROJECT, 2024
** 42sh_team
** File description:
** my_copyarray.c
*/

#include "shell.h"

char **my_copy_array(char **array)
{
    int i = 0;
    char **new = NULL;

    if (array == NULL)
        return NULL;
    for (; array[i] != NULL; i++);
    new = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; array[j] != NULL; j++)
        new[j] = my_strdup(array[j]);
    new[i] = NULL;
    return new;
}