/*
** EPITECH PROJECT, 2023
** strncmp
** File description:
** strncmp
*/

#include "shell.h"

int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    while (i < n) {
        if (s1[i] != s2[i])
            return 0;
        if (s1[i] == '\0')
            return 0;
        i++;
    }
    return 1;
}
