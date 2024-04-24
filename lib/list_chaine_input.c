/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** list_chaine_input.c
*/

#include "shell.h"

void addback_input(input_t **head, char *str)
{
    input_t *new = malloc(sizeof(input_t));
    input_t *cur = *head;

    new->seg = strdup(str);
    new->next = NULL;
    if (*head == NULL) {
        *head = new;
    } else {
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new;
    }
}

void delall_input(input_t *head)
{
    input_t *cur = head;
    input_t *del = NULL;

    while (cur != NULL) {
        del = cur;
        cur = cur->next;
        free(del->seg);
        free(del);
    }
    cur = NULL;
}

void delteindex_input(input_t **head, char *index)
{
    input_t *cur = *head;
    input_t *del = NULL;
    input_t *prev = NULL;

    if (index == NULL)
        return;
    for (; cur != NULL && my_strcmp(cur->seg, index) != 0; cur = cur->next)
        prev = cur;
    del = cur;
    if (prev != NULL) {
        prev->next = cur->next;
    } else
        *head = cur->next;
    if (my_strcmp(del->seg, index) == 0) {
        free(del->seg);
        free(del);
    }
}

void print_list_input(input_t *head)
{
    input_t *cur = head;

    for (; cur != NULL; cur = cur->next) {
        printf("%s", cur->seg);
        if (cur->next != NULL)
            printf(" ");
    }
    printf("\n");
}
