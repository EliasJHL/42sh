/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static void create_filepath(char *path, char *file)
{
    int size = my_strlen(path) + my_strlen(file) + 2;
    char *filepath = malloc(size * sizeof(char));

    my_strcpy(filepath, path);
    my_strcat(filepath, "/");
    my_strcat(filepath, file);
    free(data()->arg[data()->j][0]);
    data()->arg[data()->j][0] = filepath;
}

static int change_path(void)
{
    char *path = my_strdup(my_getenv(data()->env, "PATH"));
    char *save = my_strdup(data()->arg[data()->j][0]);
    char *file;
    char **env;

    file = strtok(path, ":");
    while (file != NULL) {
        create_filepath(file, save);
        if (access(data()->arg[data()->j][0], F_OK) == 0){
            free(path);
            free(save);
            return 1;
        }
        file = strtok(NULL, ":");
    }
    free(save);
    free(path);
    return 0;
}

void count_arg(void)
{
    data()->nb_arg_arg = malloc((data()->nb_priority + 1) * sizeof(int));
    for (int i = 0; i < data()->nb_priority + 1; i++) {
        data()->nb_arg_arg[i] = 0;
        for (int j = 0; data()->arg[i][j] != NULL; j++)
            data()->nb_arg_arg[i] += 1;
        if (data()->nb_arg_arg[i] != 0)
            data()->nb_arg_arg[i]--;
    }
}

int verif(char *input, history_t *history)
{
    if (strcmp(data()->arg[data()->j][0], "cd") == 0)
        return 1;
    if (strcmp(data()->arg[data()->j][0], "env") == 0)
        return 1;
    if (strcmp(data()->arg[data()->j][0], "setenv") == 0)
        return 1;
    if (strcmp(data()->arg[data()->j][0], "unsetenv") == 0)
        return 1;
    if (handle_specific_commands(input, history) == 0)
        return 1;
    return 0;
}

static int my_priocd2(char **input, int j)
{
    char cwd[1024];

    if (j == 1){
        if (chdir(input[1]) == -1){
            mini_printf("%s: %s.\n", input[1], strerror(errno));
        } else {
            my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
            my_setenv(&data()->env, "PWD", getcwd(cwd, sizeof(cwd)));
        }
    }
    return 1;
}

int my_priocd(char **input, int j)
{
    char cwd[1024];

    if (j > 1){
        mini_printf("cd: too many arguments\n");
        return 1;
    }
    if (j == 0){
        my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
        chdir(my_getenv(data()->env, "HOME"));
        my_setenv(&data()->env, "PWD", my_getenv(data()->env, "HOME"));
        return 1;
    }
    if (my_strcmp(input[1], "-") == 0){
        chdir(my_getenv(data()->env, "OLDPWD"));
        my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
        my_setenv(&data()->env, "PWD", getcwd(cwd, sizeof(cwd)));
        return 1;
    }
    return my_priocd2(input, j);
}

static int verif_prio2(char **input, int j)
{
    if (my_strcmp(input[0], "env") == 0)
        return disp(data()->env);
    if (handle_specific_commands(data()->input, data()->history) == 0)
        return 1;
    return 0;
}

int verif_prio(char **input, int j)
{
    if (input[0] == NULL)
        return 1;
    if (my_strcmp(input[0], "cd") == 0)
        return my_priocd(input, j);
    if (my_strcmp(input[0], "setenv") == 0){
        if (j == 2)
            return my_setenv(&data()->env, input[1], input[2]);
        if (j == 1)
            return my_setenv(&data()->env, input[1], "");
        if (j == 0)
            return disp(data()->env);
        return 1;
    }
    if (my_strcmp(data()->array[0], "unsetenv") == 0){
        for (int i = 0; input[i] != NULL; i++)
            my_unsetenv(&data()->env, input[i]);
        return 1;
    }
    return verif_prio2(input, j);
}

static int create_path2(void)
{
    if (data()->j != 0 && strcmp(data()->priority[data()->j - 1], ">") == 0) {
        data()->j++;
        return 1;
    }
    if (data()->j != 0 && strcmp(data()->priority[data()->j - 1], "<") == 0) {
        data()->j++;
        return 1;
    }
    return 0;
}

void create_path(char *input, history_t *history)
{
    char *save;

    data()->j = 0;
    while (data()->arg[data()->j] != NULL){
        save = my_strdup(data()->arg[data()->j][0]);
        if (create_path2())
            continue;
        if (COND1 || change_path()) {
            free(save);
        } else {
            mini_printf("%s: Command not found.\n", save);
            free(save);
        }
        data()->j++;
    }
    data()->j = 0;
}
