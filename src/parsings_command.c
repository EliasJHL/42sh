/*
** EPITECH PROJECT, 2024
** 42sh_team
** File description:
** parsings_command
*/

#include "shell.h"

int what_is_separator(char *str)
{
    if (str == NULL)
        return 0;
    if (my_strcmp(str, ";") == 0)
        return 1;
    if (my_strcmp(str, "&&") == 0)
        return 2;
    if (my_strcmp(str, "|") == 0)
        return 3;
    if (my_strcmp(str, ">>") == 0)
        return 4;
    if (my_strcmp(str, ">") == 0)
        return 5;
    if (my_strcmp(str, "<<") == 0)
        return 6;
    if (my_strcmp(str, "<") == 0)
        return 7;
    return 0;
}

int len_command(input_t *head)
{
    input_t *cur = head;
    int i = 0;

    while (cur != NULL) {
        if (what_is_separator(cur->seg) != 0)
            return i;
        i++;
        cur = cur->next;
    }
    return i;
}

char **command_to_exec(void)
{
    input_t *cur = data()->input;
    char **array = malloc(sizeof(char *) * (len_command(data()->input) + 1));
    int c = 0;

    while (cur != NULL) {
        if (what_is_separator(cur->seg) != 0) {
            break;
        }
        array[c] = my_strdup(cur->seg);
        c++;
        cur = cur->next;
    }
    array[c] = NULL;
    return array;
}

char **create_array(char *str)
{
    char **array = malloc(sizeof(char *) * 2);

    array[0] = my_strdup(str);
    array[1] = NULL;
    return array;
}

void parsing_command(void)
{
    data()->command = NULL;
    while (data()->input != NULL) {
        addback_command(&data()->command, command_to_exec());
        for (int i = 0; i < len_command(data()->input); i++)
            delteindex_input(&data()->input, data()->input->seg);
        if (what_is_separator(data()->input->seg) > 2) {
            addback_command(&data()->command, create_array(data()->input->seg));
            delteindex_input(&data()->input, data()->input->seg);
        } else {

        }
    }
}