/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

void clear(env_t *env)
{
    env_t *current = env;
    env_t *next;

    while (current != NULL) {
        next = current->next;
        free(current->vname);
        free(current->vcontent);
        free(current);
        current = next;
    }
}

int disp(env_t *env)
{
    while (env) {
        mini_printf("%s=", env->vname);
        if (env->vcontent != NULL)
            mini_printf("%s\n", env->vcontent);
        else
            mini_printf("\n");
        env = env->next;
    }
    return 1;
}

void add(env_t **env, char *vname, char *vcontent)
{
    env_t *new = malloc(sizeof(env_t));
    env_t *current = *env;

    new->vcontent = my_strdup(vcontent);
    new->vname = my_strdup(vname);
    new->next = NULL;
    if (*env == NULL) {
        *env = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}
