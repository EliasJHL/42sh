/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

shell_t *data(void)
{
    static shell_t *data = NULL;

    if (data == NULL)
        data = malloc(sizeof(shell_t));
    return data;
}

void free_func(char **array, int nb)
{
    for (int i = 0; data()->array[i] != NULL; i++)
        free(data()->array[i]);
    free(data()->array);
    for (int i = 0; data()->pipe[i] != NULL; i++){
        for (int j = 0; data()->pipe[i][j] != NULL; j++)
            free(data()->pipe[i][j]);
        free(data()->pipe[i]);
    }
    free(data()->pipe);
    if (nb == 1)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void init_env(char **env)
{
    int i = 0;
    int j = 0;
    char *vname;
    char *vcontent;

    data()->env = NULL;
    data()->nb_pipe = 0;
    while (env[i] != NULL){
        while (env[i][j] != '=' && env[i][j] != '\0')
            j++;
        add(&data()->env, strtok(env[i], "="), env[i] + j + 1);
        i++;
        j = 0;
    }
}

static void free_func2(char *input)
{
    free(input);
    clear(data()->env);
    free(data());
}

static int print_exit(char *input)
{
    mini_printf("exit\n");
    free_func2(input);
    return 0;
}

int mysh(char **env, history_t *history)
{
    char *input = NULL;
    size_t len = 0;
    int verif;

    while (1) {
        command_line_display(stock_display());
        //printf("$> ");
        verif = getline(&input, &len, stdin);
        if (verif == -1){
            return print_exit(input);
        }
        input[my_strlen(input) - 1] = '\0';
        add_history(&history, input);
        if (my_strcmp(input, "exit\0") == 0)
            break;
        if (verif != 1)
            separate_command(input, history);
    }
    free_func2(input);
    return 0;
}

static char **env_copy(char **env)
{
    char **new_env = NULL;
    int i = 0;

    while (env[i] != NULL)
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; j < i; j++)
        new_env[j] = strdup(env[j]);
    new_env[i] = NULL;
    return new_env;
}

static void free_copy(char **copy)
{
    int i = 0;

    while (copy[i] != NULL) {
        free(copy[i]);
        i++;
    }
    free(copy);
}

int main(int ac, char **av, char **env)
{
    char *input = NULL;
    size_t len = 0;
    history_t *history = NULL;

    init_env(env);
    if (isatty(STDIN_FILENO))
        return mysh(env, history);
    while (getline(&input, &len, stdin) != -1){
        if (input[0] != '\n'){
            input[my_strlen(input) - 1] = '\0';
            separate_command(input, history);
        }
    }
    free_func2(input);
    return 0;
}
