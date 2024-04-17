/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

int aliases(void)
{
    if (data()->nb_args == 0)
        return disp_a(data()->alias);
    if (data()->nb_args > 1){
        adding_a(&data()->alias, data()->array[1]);
        return 1;
    }
}

int unalias(void)
{
    if (data()->nb_args == 0) {
        mini_printf("unalias: Too few arguments.\n");
        return 1;
    }
    if (data()->nb_args > 1){
        for (int i = 0; data()->array[i] != NULL; i++)
            remove_a(&data()->alias, data()->array[i]);
        return 1;
    }
}
