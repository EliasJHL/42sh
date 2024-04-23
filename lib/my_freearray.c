/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_freearray.c
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
