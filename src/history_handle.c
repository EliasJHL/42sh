/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

void handle_history_command(history_t *history, char *arg)
{
    if (arg == NULL) {
        print_history(history);
        return;
    }
    if (my_getnbr(arg) >= 0){
        print_history2(history, my_getnbr(arg));
        return;
    } else {
        mini_printf("history: Badly formed number.\n");
        return;
    }
}

void execute_last_command(history_t *history)
{
    history_t *current = history;

    if (current->next != NULL) {
        while (current->next->next != NULL)
            current = current->next;
    }
    mini_printf("%s\n", current->command);
    command(current->command, history);
}

void execute_command_by_number(char *input, history_t *history)
{
    int nbr = my_getnbr(input + 1);
    history_t *command_to_execute = get_command_by_number(history, nbr);

    if (command_to_execute != NULL) {
        printf("%s\n", command_to_execute->command);
        command(command_to_execute->command, history);
    }
}

void execute_history_command(char *input, history_t *history)
{
    if (my_strcmp(input, "!!") == 0 && data()->array[1] == NULL) {
        execute_last_command(history);
    } else if (my_getnbr(input + 1) != -1) {
        execute_command_by_number(input, history);
    }
}

int handle_specific_commands(char *input, history_t *history)
{
    if (my_strcmp(data()->array[0], "history") == 0){
        handle_history_command(history, data()->array[1]);
        return 0;
    }
    if (data()->array[0][0] == '!'){
        execute_history_command(data()->array[0], history);
        return 0;
    }
    if (my_strcmp(data()->array[0], "ls") == 0){
        if (check_etoile(data()->array[1]) >= 1) {
            globbing_part1(data()->array[1]);
            return 0;
        }
    }
    return 84;
}
