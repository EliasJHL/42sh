/*
** EPITECH PROJECT, 2024
** 42sh_team
** File description:
** my_freearray
*/

#include "shell.h"

void my_freearray(char **array)
{
    int i = 0;

    if (array == NULL)
        return;
    for (; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}