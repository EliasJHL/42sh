/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

static void print_error(int error, char *command)
{
    if (errno == ENOEXEC)
        mini_printf("%s: Exec format error. Wrong Architecture.\n", command);
    else
        mini_printf("%s: %s.\n", command, strerror(errno));
}

int execute_command(char **env, char *command)
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

void launch_solo(char *input, history_t *history)
{
    char *save;
    char **env;

    if (verif_arg(data()->arg[0])){
        free_func(env, 1);
        return;
    }
    if (handle_specific_commands(input, history) == 0)
        return;
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

void launch_prio(char *input, history_t *history)
{
    int i = 0;
    char **env;

    count_arg();
    create_path(input, history);
    env = array_env(data()->env);
    data()->input = input;
    data()->history = history;
    data()->i = 0;
    data()->j = 0;
    data()->r_value = 0;
    exec_cmd(env, data()->arg[i], data()->arg[i + 1]);
}
