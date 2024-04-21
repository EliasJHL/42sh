/*
** EPITECH PROJECT, 2024
** team_42sh
** File description:
** parsings
*/

#include "shell.h"

static int check_parsing(char *buffer, char *delim)
{
    int i = 0;
    int d = 0;

    if (buffer == NULL)
        return 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == c && my_strlen(buffer) > 1)
            return 1;
        if (buffer[i + 1] == '\0' && delim[d] != '\0') {
            i = 0;
            d++;
        }
        i++;
    }
    return 0;
}

void parsing_pawn(char *buffer)
{
    char *token;
    char *ptr;
    char *temp = my_strdup(buffer);

    if (buffer[0] == ';')
        addback_input(&data()->input, ";");
    token = strtok_r(temp, ";", &ptr);
    while (token != NULL) {
        addback_input(&data()->input, token);
        if (ptr[0] != '\0' ||
            (buffer[my_strlen(buffer) - 1] == ';' && ptr[0] == '\0'))
            addback_input(&data()->input, ";");
        token = strtok_r(NULL, ";", &ptr);
    }
    free(temp);
}

int parsing(char *buffer)
{
    char *ptr;
    char *token;

    data()->input = NULL;
    token = strtok_r(buffer, " \t\n", &ptr);
    while (token != NULL) {
        if (check_parsing(token, ";") == 1) {
            parsing_pawn(token);
        } else
            addback_input(&data()->input, token);
        token = strtok_r(NULL, " \t\n", &ptr);
    }
    print_list_input(data()->input);
    del_all(data()->input);
    //print_list_input(data()->head);
    return 0;
}
