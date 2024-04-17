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
    if (data()->nb_args >= 1 && my_strcmp(data()->array[1], "*") == 0){
        for (int i = 0; data()->alias != NULL; i++)
            remove_a(&data()->alias, data()->alias->alias);
        return 1;
    }
    if (data()->nb_args >= 1){
        for (int i = 0; data()->array[i] != NULL; i++)
            remove_a(&data()->alias, data()->array[i]);
        return 1;
    }
}

void alias_to_cmd(alias_t *alias)
{
    int size = data()->nb_args + alias->nb_command;
    char **temp = malloc(sizeof(char *) * (size + 1));
    int i = 0;

    while (alias->command[i] != NULL){
        temp[i] = my_strdup(alias->command[i]);
        i++;
    }
    for (int j = 1; data()->array[j] != NULL; j++){
        temp[i] = my_strdup(data()->array[j]);
        i++;
    }
    temp[i] = NULL;
    for (int i = 0; data()->array[i] != NULL; i++)
        free(data()->array[i]);
    free(data()->array);
    data()->array = temp;
    data()->nb_args = size;
}

void check_alias(void)
{
    alias_t *current = data()->alias;

    while (current != NULL){
        if (my_strcmp(data()->array[0], current->alias) == 0){
            alias_to_cmd(current);
            return;
        }
        current = current->next;
    }
}
