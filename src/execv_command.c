/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** execv_command.c
*/

#include "shell.h"

static int verif_arg2(char **input)
{
    if (my_strcmp(input[0], "env") == 0)
        return disp(data()->env);
    return 0;
}

int verif_arg(char **input)
{
    if (input == NULL)
        return 1;
    if (my_strcmp(input[0], "cd") == 0)
        return my_cd();
    if (my_strcmp(input[0], "setenv") == 0){
        if (my_arraylen(input) == 3)
            return my_setenv(&data()->env, input[1], input[2]);
        if (my_arraylen(input) == 2)
            return my_setenv(&data()->env, input[1], "");
        if (my_arraylen(input) == 1)
            return disp(data()->env);
        return 1;
    }
    if (my_strcmp(input[0], "unsetenv") == 0){
        for (int i = 0; input[i] != NULL; i++)
            my_unsetenv(&data()->env, input[i]);
        return 1;
    }
    return verif_arg2(input);
}


static void print_error(int error, char *command)
{
    if (errno == ENOEXEC)
        mini_printf("%s: Exec format error. Wrong Architecture.\n", command);
    else
        mini_printf("%s: %s.\n", command, strerror(errno));
}

static int execute_command(char **env, char *command)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        if (execve(data()->command->command_a[0], data()->command->command_a, env) == -1){
            print_error(errno, command);
            exit(0);
        }
    } else {
        waitpid(pid, &status, 0);
        if (status == 139)
            mini_printf("Segmentation fault (core dumped)\n");
        if (status == 11)
            mini_printf("Segmentation fault\n");
    }
    return 0;
}

static void create_filepath(char *path, char *file)
{
    int size = my_strlen(path) + my_strlen(file) + 2;
    char *filepath = malloc(size * sizeof(char));

    my_strcpy(filepath, path);
    my_strcat(filepath, "/");
    my_strcat(filepath, file);
    free(data()->command->command_a[0]);
    data()->command->command_a[0] = filepath;
}

int search_path(void)
{
    char *path = my_strdup(my_getenv(data()->env, "PATH"));
    char *save = my_strdup(data()->command->command_a[0]);
    char *file;
    char **env;

    file = strtok(path, ":");
    while (file != NULL) {
        create_filepath(file, save);
        if (access(data()->command->command_a[0], F_OK) == 0) {
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

int command(void)
{
    char **env;
    char *save;

    if (verif_arg(data()->command->command_a)){
        delteindex_command(&data()->command, data()->command->command_a);
        return 1;
    }
    save = my_strdup(data()->command->command_a[0]);
    if (access(data()->command->command_a[0], F_OK) == 0 || search_path()) {
        env = array_env(data()->env);
        execute_command(env, save);
        delteindex_command(&data()->command, data()->command->command_a);
        my_freearray(env);
        free(save);
        return 1;
    } else
        mini_printf("%s: Command not found.\n", save);
    free(save);
    delteindex_command(&data()->command, data()->command->command_a);
    return 0;
}