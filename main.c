/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main.c
*/

#include "include/shell.h"

// typedef struct input_s {
//     char *seg;
//     struct input_s *next;
// } input_t;

// char *me_strcat(char *dest, char *src)
// {
//     int j = 0;
//     int dest_len = strlen(dest);
//     int src_len = strlen(src);
//     char *copy = malloc(sizeof(char) * (dest_len + src_len) + 1);

//     for (int i = 0; i < dest_len; i++)
//         copy[i] = dest[i];
//     for (j = 0; j < src_len; j++)
//         copy[dest_len + j] = src[j];
//     copy[dest_len + j] = '\0';
//     return copy;
// }

// /* list_chainé */

// void addback_input(input_t **head, char *str)
// {
//     input_t *new = malloc(sizeof(input_t));
//     input_t *cur = *head;

//     new->seg = strdup(str);
//     new->next = NULL;
//     if (*head == NULL) {
//         *head = new;
//     } else {
//         while (cur->next != NULL) {
//             cur = cur->next;
//         }
//         cur->next = new;
//     }
// }

// void del_all(input_t *head)
// {
//     input_t *cur = head;
//     input_t *del = NULL;

//     while (cur != NULL) {
//         del = cur;
//         cur = cur->next;
//         free(del->seg);
//         free(del);
//     }
// }

// void delte_they(input_t **head, input_t *cur)
// {
//     input_t *del = &
//     input_t *prev = *head;

//     if (cur->next == NULL) {
//         cur = NULL;
//     } else {
//         cur = cur->next;
//     }
//     free(del->seg);
//     free(del);
// }
// {
//     input_t *del = cur;

//     if (cur->next == NULL)
//         cur = NULL;
//     else
//         cur = cur->next;
//     free(del->seg);
//     free(del);
// }
// /* list_chainé */

// static int check_inhibitor(char *str)
// {
//     int i = 0;
    
//     while (str[i] != '\0') {
//         if (str[i] == '\"')
//             return 1;
//         if (str[i] == '\'')
//             return 1;
//         i++;
//     }
//     return 0;
// }

// void inhibitor(input_t *origin)
// {
//     input_t *cur = origin->next;
//     char *temp;

//     do {
//         if (cur == NULL)
//             break;
//         temp = strdup(cur->seg);
//         origin->seg = me_strcat(origin->seg, " ");
//         origin->seg = me_strcat(origin->seg, cur->seg);
//         delte_they(cur);
//     } while (check_inhibitor(temp) != 1);
// }


// void parsing_inhibitor(input_t *head)
// {
//     input_t *cur = head;

//     while (cur != NULL) {
//         if (!check_inhibitor(cur->seg))
//             inhibitor(cur);
//         cur = cur->next;
//     }
// }

// void print_list(input_t *head)
// {
//     input_t *cur = head;

//     while (cur != NULL) {
//         printf("%s\n", cur->seg);
//         cur = cur->next;
//     }
// }

// int parsing(char *buffer)
// {
//     input_t *head = NULL;
//     char *ptr;
//     char *token;

//     token = strtok_r(buffer, " \t\n", &ptr);
//     while (token != NULL) {
//         addback_node(&head, token);
//         token = strtok_r(NULL, " \t\n", &ptr);
//     }
//     parsing_inhibitor(head);
//     print_list(head);
//     return 0;
// }

// int main(void)
// {
//     char *buffer = NULL;
//     size_t len = 0;

//     while (1) {
//         printf("$> ");
//         getline(&buffer, &len, stdin);
//         buffer[strlen(buffer) - 1] = '\0';
//         if (strcmp(buffer, "exit") == 0)
//             break;
//         parsing(buffer);
//     }
//     return 0;
// }

int main(int ac, char **av)
{
    char *buffer;
    char *ptr;

    if (ac != 2)
        return 84;
    buffer = strtok_r(av[1], "&", &ptr);
    while (buffer != NULL) {
        printf("buffer: %s && ptr: %s\n", buffer, ptr);
        buffer = strtok_r(NULL, "&", &ptr);
    }
    return 0;
}