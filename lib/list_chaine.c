/*
** EPITECH PROJECT, 2024
** team_42sh
** File description:
** list_chaine
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

void add_middel(input_t **head, char *str)
{
    input_t *new = malloc(sizeof(input_t));
    input_t *cur = *head;

    new->seg = strdup(str);
    if (*head == NULL) {
        new->next = NULL;
        *head = new;
    }else if (cur->next == NULL) {
        new->next = NULL;
        cur->next = new;
    } else {
        new->next = cur->next;
        cur->next = new;
    }
}

void del_all(input_t *head)
{
    input_t *cur = head;
    input_t *del = NULL;

    while (cur != NULL) {
        del = cur;
        cur = cur->next;
        free(del->seg);
        free(del);
    }
}