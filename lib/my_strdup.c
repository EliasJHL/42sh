/*
** EPITECH PROJECT, 2023
** strdup
** File description:
** strdup
*/

#include "shell.h"
#include <stdlib.h>

char *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strdup(char *str)
{
    int len;
    char *dest;

    len = my_strlen(str);
    dest = (char *)malloc(len + 1);
    dest = my_strcpy(dest, str);
    return dest;
}
