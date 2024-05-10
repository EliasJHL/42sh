/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static int is_priority(char *str)
{
    if (my_strcmp(str, "<") == 0)
        return 1;
    if (my_strcmp(str, ">") == 0)
        return 1;
    if (my_strcmp(str, ">>") == 0)
        return 1;
    if (my_strcmp(str, "<<") == 0)
        return 1;
    if (my_strcmp(str, "&&") == 0)
        return 1;
    if (my_strcmp(str, "||") == 0)
        return 1;
    if (my_strcmp(str, "&") == 0)
        return 1;
    if (my_strcmp(str, "|") == 0)
        return 1;
    return 0;
}

static int verif_priority(int i)
{
    if (i == 0)
        return 1;
    if (COMPARR(i - 1, "<") == 0 || COMPARR(i - 1, ">") == 0)
        return 1;
    if (COMPARR(i - 1, ">>") == 0 || COMPARR(i - 1, "<<") == 0)
        return 1;
    if (COMPARR(i - 1, "&&") == 0 || COMPARR(i - 1, "||") == 0)
        return 1;
    if (COMPARR(i - 1, "&") == 0 || COMPARR(i - 1, "|") == 0)
        return 1;
    if (COMPARR(i + 1, "<") == 0 || COMPARR(i + 1, ">") == 0)
        return 1;
    if (COMPARR(i + 1, ">>") == 0 || COMPARR(i + 1, "<<") == 0)
        return 1;
    if (COMPARR(i + 1, "&&") == 0 || COMPARR(i + 1, "||") == 0)
        return 1;
    if (COMPARR(i + 1, "&") == 0 || COMPARR(i + 1, "|") == 0)
        return 1;
    data()->nb_priority += 1;
    return 0;
}

int count_priority3(int i)
{
    if (COMPARR(i, "&&") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    if (COMPARR(i, "||") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    if (COMPARR(i, "&") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    if (COMPARR(i, "|") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    return 0;
}

int count_priority2(int i)
{
    if (COMPARR(i, "<") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    if (COMPARR(i, ">") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    if (COMPARR(i, ">>") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    if (COMPARR(i, "<<") == 0 && data()->array[i + 1] != NULL)
        if (verif_priority(i))
            return 1;
    return 0;
}

int count_priority(void)
{
    data()->nb_priority = 0;
    for (int i = 0; data()->array[i] != NULL; i++) {
        if (count_priority2(i))
            return 1;
        if (count_priority3(i))
            return 1;
    }
    return 0;
}

int copy_arg(int i, int j)
{
    int k = i;
    int l = 0;

    while (data()->array[k + 1] != NULL && !is_priority(data()->array[k + 1])){
        k++;
    }
    data()->arg[j] = malloc((k + 2) * sizeof(char *));
    while (data()->array[i] != NULL && !is_priority(data()->array[i])){
        data()->arg[j][l] = my_strdup(data()->array[i]);
        i++;
        l++;
    }
    data()->arg[j][l] = NULL;
    return i;
}

int separate_priority(void)
{
    int i = 0;
    int j = 0;
    int k = 0;

    if (count_priority())
        return 1;
    data()->arg = malloc((data()->nb_priority + 2) * sizeof(char **));
    data()->priority = malloc((data()->nb_priority + 1) * sizeof(char *));
    while (j < data()->nb_priority + 1) {
        i = copy_arg(i, j);
        if (k < data()->nb_priority) {
            data()->priority[k] = my_strdup(data()->array[i]);
            k++;
        }
        i++;
        j++;
    }
    data()->priority[k] = NULL;
    data()->arg[j] = NULL;
    return 0;
}
