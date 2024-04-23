/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_arraycmp.c
*/

#include "shell.h"

int my_arraycmp(char **array1, char **array2)
{
    int i = 0;

    if (array1 == NULL || array2 == NULL)
        return -1;
    for (; array1[i] != NULL && array2[i] != NULL; i++) {
        if (my_strcmp(array1[i], array2[i]) != 0)
            return 1;
    }
    if (array1[i] != NULL && array2[i] != NULL)
        return 1;
    return 0;
}
