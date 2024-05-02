/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

int check_etoile(char *str)
{
    int nbr = 0;

    if (str == NULL)
        return -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*')
            nbr++;
        if (str[i] == '?')
            nbr++;
    }
    return nbr;
}

void globbing_part1(char *str)
{
    glob_t glob_result;

    glob(str, GLOB_TILDE, NULL, &glob_result);
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
        printf("%s\n", glob_result.gl_pathv[i]);
    }
    globfree(&glob_result);
}
