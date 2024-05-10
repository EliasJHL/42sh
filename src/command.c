/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static int my_cd2(char **input)
{
    char cwd[1024];

    if (data()->nb_args == 1){
        if (chdir(input[1]) == -1){
            mini_printf("%s: %s.\n", input[1], strerror(errno));
        } else {
            my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
            my_setenv(&data()->env, "PWD", getcwd(cwd, sizeof(cwd)));
        }
    }
    return 1;
}

int my_cd(char **input)
{
    char cwd[1024];

    if (data()->nb_args > 1){
        mini_printf("cd: too many arguments\n");
        return 1;
    }
    if (data()->nb_args == 0){
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
    return my_cd2(input);
}

static int verif_arg2(char **input)
{
    if (my_strcmp(input[0], "env") == 0)
        return disp(data()->env);
    return 0;
}

int verif_arg(char **input)
{
    if (input[0] == NULL)
        return 1;
    if (my_strcmp(input[0], "cd") == 0)
        return my_cd(input);
    if (my_strcmp(input[0], "setenv") == 0){
        if (data()->nb_args == 2)
            return my_setenv(&data()->env, input[1], input[2]);
        if (data()->nb_args == 1)
            return my_setenv(&data()->env, input[1], "");
        if (data()->nb_args == 0)
            return disp(data()->env);
        return 1;
    }
    if (my_strcmp(data()->array[0], "unsetenv") == 0){
        for (int i = 0; input[i] != NULL; i++)
            my_unsetenv(&data()->env, input[i]);
        return 1;
    }
    return verif_arg2(input);
}

static void create_filepath(char *path, char *file)
{
    int size = my_strlen(path) + my_strlen(file) + 2;
    char *filepath = malloc(size * sizeof(char));

    my_strcpy(filepath, path);
    my_strcat(filepath, "/");
    my_strcat(filepath, file);
    free(data()->array[0]);
    data()->array[0] = filepath;
}

int search_path(void)
{
    char *path = my_strdup(my_getenv(data()->env, "PATH"));
    char *save = my_strdup(data()->array[0]);
    char *file;
    char **env;

    file = strtok(path, ":");
    while (file != NULL) {
        create_filepath(file, save);
        if (access(data()->array[0], F_OK) == 0){
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

void execute_command_if_exists(char *command, char **env)
{
    char *save = my_strdup(command);

    if (access(command, F_OK) == 0 || search_path()){
        execute_command(env, save);
        free_func(env, 0);
        free(save);
        return;
    } else {
        mini_printf("%s: Command not found.\n", save);
        free(save);
        free_func(env, 1);
    }
}

void command(char *input, history_t *history)
{
    char **env;
    char *save;
    int i = 0;

    separate_arg(input);
    if (separate_priority())
        return;
    if (data()->nb_priority != 0){
        launch_prio(input, history);
        return;
    }
    launch_solo(input, history);
}
