/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static int my_cd2(void)
{
    char cwd[1024];

    if (data()->nb_args == 1){
        if (chdir(data()->array[1]) == -1){
            mini_printf("%s: %s.\n", data()->array[1], strerror(errno));
        } else {
            my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
            my_setenv(&data()->env, "PWD", getcwd(cwd, sizeof(cwd)));
        }
    }
    return 1;
}

int my_cd(void)
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
    if (my_strcmp(data()->array[1], "-") == 0){
        chdir(my_getenv(data()->env, "OLDPWD"));
        my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
        my_setenv(&data()->env, "PWD", getcwd(cwd, sizeof(cwd)));
        return 1;
    }
    return my_cd2();
}

static int verif_arg2(void)
{
    if (my_strcmp(data()->array[0], "env") == 0)
        return disp(data()->env);
    if (my_strcmp(data()->array[0], "alias") == 0)
        return aliases();
    return 0;
}

int verif_arg(void)
{
    if (data()->array[0] == NULL)
        return 1;
    if (my_strcmp(data()->array[0], "cd") == 0)
        return my_cd();
    if (my_strcmp(data()->array[0], "setenv") == 0){
        if (data()->nb_args == 2)
            return my_setenv(&data()->env, data()->array[1], data()->array[2]);
        if (data()->nb_args == 1)
            return my_setenv(&data()->env, data()->array[1], "");
        if (data()->nb_args == 0)
            return disp(data()->env);
        return 1;
    }
    if (my_strcmp(data()->array[0], "unsetenv") == 0){
        for (int i = 0; data()->array[i] != NULL; i++)
            my_unsetenv(&data()->env, data()->array[i]);
        return 1;
    }
    return verif_arg2();
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
        if (execve(data()->array[0], data()->array, env) == -1){
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

void command(char *input)
{
    char **env;
    char *save;

    separate_arg(input);
    separate_pipe();
    if (verif_arg()){
        free_func(env, 1);
        return;
    }
    save = my_strdup(data()->array[0]);
    if (access(data()->array[0], F_OK) == 0 || search_path()){
        env = array_env(data()->env);
        execute_command(env, save);
        free_func(env, 0);
        free(save);
        return;
    } else
        mini_printf("%s: Command not found.\n", save);
        free(save);
        free_func(env, 1);
}
