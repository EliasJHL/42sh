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
