/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

void print_history(history_t *history)
{
    int i = 0;
    history_t *tmp = history;
    char time_str[20];

    while (tmp) {
        strftime(time_str, sizeof(time_str), "%H:%M", localtime(&(tmp->time)));
        mini_printf("     %d  %s  %s\n", i, time_str, tmp->command);
        tmp = tmp->next;
        i++;
    }
}

void print_commands_from(history_t *start, int nbr)
{
    char str[20];

    while (start) {
        strftime(str, sizeof(str), "%H:%M", localtime(&(start->time)));
        mini_printf("     %d  %s  %s\n", nbr, str, start->command);
        start = start->next;
        nbr++;
    }
}

void print_history2(history_t *history, int nbr)
{
    int total = 0;
    int start = 0;
    history_t *tmp = history;
    char time_str[20];

    if (nbr <= 1)
        nbr = 1;
    while (tmp) {
        total++;
        tmp = tmp->next;
    }
    start = total - nbr;
    tmp = history;
    for (int i = 0; i < start; i++)
        tmp = tmp->next;
    nbr = start;
    print_commands_from(tmp, nbr);
}

int add_history(history_t **history, char *command)
{
    history_t *new_node = malloc(sizeof(history_t));
    history_t *current = *history;

    if (!new_node)
        return 84;
    new_node->command = strdup(command);
    new_node->time = time(NULL);
    new_node->next = NULL;
    if (!(*history)) {
        *history = new_node;
        return 0;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
    return 0;
}

history_t *get_command_by_number(history_t *history, int nbr)
{
    history_t *current = history;
    int i = 0;

    while (current != NULL) {
        if (i == nbr) {
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL;
}
