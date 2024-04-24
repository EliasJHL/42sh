/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_arraylen.c
*/

#include "shell.h"

int my_arraylen(char **array)
{
    int i = 0;

    if (array == NULL)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}
