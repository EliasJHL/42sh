/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static void print_alias(alias_t *alias)
{
    int i = 0;

    if (alias->nb_command > 2){
        mini_printf("(");
        while (alias->command[i + 1] != NULL){
            mini_printf("%s ", alias->command[i]);
            i++;
        }
        mini_printf("%s", alias->command[i]);
        mini_printf(")\n");
    } else
        mini_printf("%s\n", alias->command[0]);
}

int disp_a(alias_t *alias)
{
    while (alias) {
        mini_printf("%s\t", alias->alias);
        if (alias->command != NULL)
            print_alias(alias);
        else
            mini_printf("\n");
        alias = alias->next;
    }
    return 1;
}

void add_a(alias_t **alias, char *name)
{
    alias_t *new = malloc(sizeof(alias_t));
    alias_t *current = *alias;

    new->alias = my_strdup(name);
    new->command = malloc(sizeof(char *) * data()->nb_args);
    for (int i = 0; i < data()->nb_args - 1; i++)
        new->command[i] = my_strdup(data()->array[i + 2]);
    new->command[data()->nb_args - 1] = NULL;
    new->nb_command = data()->nb_args;
    new->next = NULL;
    if (*alias == NULL) {
        *alias = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

void adding_a(alias_t **alias, char *name)
{
    int i = 0;
    alias_t *current = *alias;
    alias_t *previous = NULL;

    while (current && my_strcmp(current->alias, name) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL){
        add_a(&data()->alias, name);
        return;
    }
    for (int i = 0; current->command[i] != NULL; i++)
        free(current->command[i]);
    free(current->command);
    current->command = malloc(sizeof(char *) * data()->nb_args);
    while (i < data()->nb_args - 1){
        current->command[i] = my_strdup(data()->array[i + 2]);
        i++;
    }
    current->command[i] = NULL;
    current->nb_command = data()->nb_args;
}
