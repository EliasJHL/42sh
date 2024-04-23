/*
** EPITECH PROJECT, 2024
** 42sh_team
** File description:
** parsings_command
*/

#include "shell.h"

int what_is_separator(input_t *head)
{
    if (head == NULL)
        return 0;
    if (my_strcmp(head->seg, ";") == 0)
        return 1;
    if (my_strcmp(head->seg, "&&") == 0)
        return 2;
    if (my_strcmp(head->seg, "|") == 0)
        return 3;
    if (my_strcmp(head->seg, ">>") == 0)
        return 4;
    if (my_strcmp(head->seg, ">") == 0)
        return 5;
    if (my_strcmp(head->seg, "<<") == 0)
        return 6;
    if (my_strcmp(head->seg, "<") == 0)
        return 7;
    return -1;
}

static int len_command(input_t *head)
{
    input_t *cur = head;
    int i = 0;

    while (cur != NULL) {
        if (what_is_separator(cur) > 0)
            return i;
        i++;
        cur = cur->next;
    }
    return i;
}

static void delte_command(void)
{
    list_command_t *cur = data()->command;

    for (; cur->next != NULL; cur = cur->next);
    for (int i = 0; cur->command_a[i] != NULL; i++)
        delteindex_input(&data()->input, cur->command_a[i]);
}

static char **command_to_exec(void)
{
    int nb = 0;
    input_t *cur = data()->input;
    int len = len_command(data()->input);
    char **array = malloc(sizeof(char *) * (len + 1));
    int c = 0;

    while (cur != NULL) {
        if (what_is_separator(cur) > 0) {
            break;
        }
        array[c] = my_strdup(cur->seg);
        c++;
        cur = cur->next;
    }
    array[c] = NULL;
    return array;
}

static char **create_array(char *str)
{
    char **array = malloc(sizeof(char *) * 2);

    array[0] = my_strdup(str);
    array[1] = NULL;
    return array;
}

int command_par(void)
{
    int seperator = 0;

    if (data()->input == NULL)
        return 1;
    seperator = what_is_separator(data()->input);
    if (seperator > 2) {
        addback_command(&data()->command, create_array(data()->input->seg));
        delteindex_input(&data()->input, data()->input->seg);
        return 0;
    } else if (seperator > -1 && seperator < 3)
        return 1;
}

void what_exevcute(int seperator)
{
    if (seperator == 1)
        delteindex_input(&data()->input, ";");
    if (seperator == 2)
        delteindex_input(&data()->input, "&&");
}

void parsing_command(void)
{
    data()->command = NULL;
    while (data()->input != NULL) {
        addback_command(&data()->command, command_to_exec());
        delte_command();
        if (command_par() == 1) {
            print_list_command(data()->command);
            what_exevcute(what_is_separator(data()->input));
            delall_commmand(data()->command);
            data()->command = NULL;
        }
    }
    if (data()->command != NULL)
        delall_commmand(data()->command);
    data()->command = NULL;
}
