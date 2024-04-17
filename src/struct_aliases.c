/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

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