/*
** EPITECH PROJECT, 2023
** workshoplib
** File description:
** my_getnbr
*/

#include "shell.h"

int find_number(char const *str, int i)
{
    int nb = str[i] - '0';

    while (str[i + 1] > 47 && str[i + 1] <= 57) {
        nb = nb * 10;
        nb = nb + (str[i + 1] - '0');
        i++;
    }
    return nb;
}

int check_errorr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-' || (str[i] < '0' || str[i] > '9')) {
            return -1;
        }
    }
    return 0;
}

int my_getnbr(char const *str)
{
    int nb;
    int j = 0;

    if (check_errorr(str) == -1)
        return -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 48 && str[i] <= 57) {
            nb = find_number(str, i);
            return nb;
        }
    }
}
