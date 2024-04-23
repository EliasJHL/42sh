/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** list_chaine_command.c
*/

#include "shell.h"

void addback_command(list_command_t **head, char **array)
{
    list_command_t *new = malloc(sizeof(list_command_t));
    list_command_t *cur = *head;

    new->command_a = my_copy_array(array);
    my_freearray(array);
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

void delall_commmand(list_command_t *head)
{
    list_command_t *cur = head;
    list_command_t *del = NULL;

    while (cur != NULL) {
        del = cur;
        cur = cur->next;
        my_freearray(del->command_a);
        free(del);
    }
    cur = NULL;
}

void delteindex_command(list_command_t **head, char **index)
{
    list_command_t *cur = *head;
    list_command_t *del = NULL;
    list_command_t *prev = NULL;

    for (; cur != NULL; cur = cur->next) {
        if (my_arraycmp(cur->command_a, index) == 0)
            break;
        prev = cur;
    }
    del = cur;
    if (prev != NULL) {
        prev->next = cur->next;
    } else
        *head = cur->next;
    my_freearray(del->command_a);
    free(del);
}

static void print_command(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s", array[i]);
        if (array[i + 1] != NULL)
            printf(" ");
    }
}

void print_list_command(list_command_t *head)
{
    list_command_t *cur = head;
    int i = 0;

    if (head == NULL){
        return;
    }
    for (; cur != NULL; cur = cur->next) {
        print_command(cur->command_a);
        if (cur->next != NULL)
            printf(" ");
    }
    printf("\n");
}
