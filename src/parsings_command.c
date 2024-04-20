/*
** EPITECH PROJECT, 2024
** team_42sh
** File description:
** parsings
*/

#include "shell.h"

static int check_parsing(char *buffer)
{
    int i = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == ';' && my_strlen(buffer) > 1)
            return 1;
    }
    return 0;
}

static void cut_pawn(input_t *head)
{
    input_t *cur = head;
    char *token;
    char *ptr;

    token = strtok_r(NULL, ";", &ptr);
    while (token != NULL) {
        add_middel(, token);
        token = strtok_r(NULL, ";", &ptr);
    }
}

void parsing_pawn(input_t *head)
{
    input_t *cur = head;

    while (cur != NULL) {
        if (check_parsing(cur->seg) == 1)
            cut_pawn(cur);
       cur = cur->next;
    }
}

int parsing(char *buffer)
{
    input_t *head = NULL;
    char *ptr;
    char *token;

    token = strtok_r(buffer, " \t\n", &ptr);
    while (token != NULL) {
        addback_node(&head, token);
        token = strtok_r(NULL, " \t\n", &ptr);
    }
    return 0;
}
