/*
** EPITECH PROJECT, 2024
** my_strskipcpy
** File description:
** my_strskipcpy
*/

#include "shell.h"

void my_strskipcpy(char *dest, const char *src, int skip)
{
    int i = 0;

    while (src[skip] != '\0') {
        dest[i] = src[skip];
        skip++;
        i++;
    }
    dest[i] = '\0';
}
