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

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int k = 0;

    while (dest[k] != '\0') {
        k++;
    }
    while (src[i] != '\0') {
        dest[i + k] = src[i];
        i++;
    }
    dest[i + k] = '\0';
    return dest;
}

/* list_chainé */

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
            cur = cur->next;
        }
        cur = new;
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

void delte_they(input_t *cur,  input_t *origin)
{
    input_t *del = cur;

    if (cur->next == NULL)
        cur = NULL;
    else
        cur = cur->next;
    origin->next = cur;
    free(del->seg);
    free(del);
}
/* list_chainé */

static int check_inhibitor(char *str)
{
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == '\"')
            return 1;
        if (str[i] == '\'')
            return 1;
    }
    return 0;
}

void inhibitor(input_t *origin)
{
    input_t *cur = origin->next;
    char *temp;

    origin->seg = my_strcat(origin->seg, " ");
    origin->seg = my_strcat(origin->seg, cur->seg);
    do {
        if (cur == NULL)
            break;
        temp = strdup(cur->seg);
        origin->seg = my_strcat(origin->seg, " ");
        origin->seg = my_strcat(origin->seg, cur->seg);
        delte_they(cur, origin);
    } while (check_inhibitor(temp) != 1);
}


void parsing_inhibitor(input_t *head)
{
    input_t *cur = head;

    while (cur != NULL) {
        if (!check_inhibitor(cur->seg))
            inhibitor(cur);
        cur = cur->next;
    }
}

int listlen(input_t *head)
{
    input_t *cur = head;
    int ndcomt = 0;

    while (cur != NULL) {
        ndcomt++;
        cur = cur->next;
    }
    return 0;
}

char **create_array(input_t *head)
{
    int nbword = listlen(head);
    input_t *cur = head;
    char **array = malloc(sizeof(char *) * (nbword + 1));
    int i = 0;

    while (cur != NULL) {
        array[i] = strdup(cur->seg);
        cur = cur->next;
        i++;
    }
    array[i] = NULL;
    del_all(head);
    return array;
}

char **cut_arg(char *buffer)
{
    char **array;
    input_t *head = malloc(sizeof(input_t));
    char *ptr;
    char *token;

    printf("step: 1\n");
    token = strtok_r(buffer, " \t\n", &ptr);
    printf("step: 2 - %s\n", token);
    while (token != NULL) {
        if (token == NULL)
            break;
        printf("step: 2 - %s\n", token);
        addback_node(head, token);
        token = strtok_r(NULL, " \t\n", &ptr);
    }
    printf("step: 3\n");
    parsing_inhibitor(head);
    array = create_array(head);
    return array;
}

int main(int ac, char **av)
{
    char *buffer = NULL;
    size_t len = 0;
    char **input = NULL;
    int verif = 0;

    while (1) {
        printf("$> ");
        verif = getline(&buffer, &len, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(buffer, "exit") == 0)
            break;
        input = cut_arg(buffer);
        while (*input != NULL) {
            printf("%s-\n", input[0]);
            *input++;
        }
    }
    return 0;
}