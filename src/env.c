/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

int size_list(env_t *env)
{
    env_t *current = env;
    int nb = 0;

    while (current){
        nb++;
        current = current->next;
    }
    return nb;
}

char **array_env(env_t *env)
{
    env_t *current = env;
    char **array = malloc((size_list(env) + 1) * sizeof(char *));
    char *temp;
    int size;
    int i = 0;

    while (current) {
        size = my_strlen(current->vname) + my_strlen(current->vcontent) + 2;
        temp = malloc(size * sizeof(char));
        my_strcpy(temp, current->vname);
        my_strcat(temp, "=");
        my_strcat(temp, current->vcontent);
        array[i] = temp;
        i++;
        current = current->next;
    }
    array[i] = NULL;
    return array;
}

void my_unsetenv(env_t **env, char *vname)
{
    env_t *current = *env;
    env_t *previous = NULL;

    while (current && my_strcmp(current->vname, vname) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    if (previous != NULL) {
        previous->next = current->next;
    } else
        *env = current->next;
    free(current->vname);
    free(current->vcontent);
    free(current);
}

static int verif_char(char *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (!is_letter(str[i]) && !is_number(str[i]) && str[i] != '_')
            return 1;
        i++;
    }
    return 0;
}

int my_setenv(env_t **env, char *vname, char *vcontent)
{
    env_t *current = *env;
    env_t *previous = NULL;

    if (verif_char(vname)){
        mini_printf("setenv: Variable name must contain");
        mini_printf(" alphanumeric characters.\n");
        return 1;
    }
    while (current && my_strcmp(current->vname, vname) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL){
        add(&data()->env, vname, vcontent);
        return 1;
    }
    free(current->vcontent);
    current->vcontent = my_strdup(vcontent);
    return 1;
}

char *my_getenv(env_t *env, char *vname)
{
    env_t *current = env;

    while (current && my_strcmp(current->vname, vname) != 0) {
        current = current->next;
    }
    if (current == NULL)
        return "HOME";
    return current->vcontent;
}
