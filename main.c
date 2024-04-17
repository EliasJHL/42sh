/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main.c
*/

#include "include/shell.h"

typedef struct input_s {
    char *seg;
    struct input_s *next;
} input_t;

void addback_node(input_t *head, char *str)
{
    input_t *new = malloc(sizeof(input_t));
    input_t *cur = head;
    
    new->seg = strdup(str);
    new->next = NULL;
    if (cur == NULL) {
        cur = new;
    } else {
        while (cur != NULL) {
            cuir = cur->next;
        }
        cur = new;
    }
}

static int check_inhibitor(char *str)
{
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == '\"')
            return 1;
        if (str[i] == '\'')
            return 1;
        if (str[i] == '\\')
            return 1;
    }
    return 0;
}

void inhibitor(input_t *head, int *nbword)
{
    input_t *cur = head;

    while (cur != NULL) {
        if (check_inhibitor(cur->seg))

        cur = cur->next;
    }
}


char **cut_arg(char *buffer)
{
    char **array;
    input_t *head = malloc(sizeof(input_t));
    char *ptr;
    char *token;
    int nbword = 0;
    
    token = strtok_r(buffer, " \t\n", &ptr);
    while (token != NULL) {
        add(head, token);
        nbword++;
        token = strtok_r(buffer, " \t\n", &ptr);
    }
}

int main(int ac, char **av)
{
    char *buffer = NULL;
    size_t len = 0;
    int verif = 0;

    while (1) {
        printf("$> ");
        verif = getline(&buffer, &len, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(buffer, "exit") == 0)
            break;
    }
    return 0;
}