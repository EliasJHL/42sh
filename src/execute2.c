/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

void exec_redir_left(char **env, char **cmd, char *filename)
{
    int fd;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        fd = open(filename, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
        execve(cmd[0], cmd, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}

static void get_input(char *word)
{
    char *input = NULL;
    size_t len = 0;
    int fd;

    fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    mini_printf("> ");
    while (getline(&input, &len, stdin) != -1) {
        if (strncmp(input, word, strlen(input) - 1) == 0)
            break;
        write(fd, input, strlen(input));
        mini_printf("> ");
    }
    close(fd);
}

void exec_dredir_left(char **env, char **cmd, char *word)
{
    char *input = NULL;
    size_t len = 0;
    int fd;
    pid_t pid;

    get_input(word);
    pid = fork();
    if (pid == 0) {
        fd = open("tmp", O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
        execve(cmd[0], cmd, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    remove("tmp");
}

void get_false_return(int status)
{
    if (WIFEXITED(status) && WEXITSTATUS(status) == 1){
        data()->r_value = 1;
    }
}

static void new_exec(char **env)
{
    if (data()->arg[data()->j] != NULL && data()->priority[data()->i] != NULL){
        data()->r_value = 0;
        exec_cmd(env, data()->arg[data()->j], data()->arg[data()->j + 1]);
    }
}

static int error_fork(char **env)
{
    if (verif_prio(data()->arg[data()->j], data()->j - 1))
        return 0;
    execve(data()->arg[data()->j][0], data()->arg[data()->j], env);
    return 1;
}

static void exec_dpipes2(char **env)
{
    int status;
    pid_t pid;

    if (data()->arg[data()->j + 1] == NULL && data()->r_value == 1) {
        pid = fork();
        if (pid == 0) {
            exit(error_fork(env));
        }
        wait(&status);
        return;
    }
}

void exec_dpipes(char **env)
{
    pid_t pid;
    int status;

    while (COND2 && data()->priority[data()->i] != NULL) {
        if (strcmp(data()->priority[data()->i], "||") != 0)
            break;
        pid = fork();
        if (pid == 0) {
            execve(data()->arg[data()->j][0], data()->arg[data()->j], env);
            exit(0);
        }
        waitpid(pid, &status, 0);
        get_false_return(status);
        if (WEXITSTATUS(status) == 0 && data()->r_value == 0)
            return;
        data()->j++;
        data()->i++;
    }
    exec_dpipes2(env);
    new_exec(env);
}

static void exec_and2(char **env)
{
    int status;
    pid_t pid;

    if (data()->arg[data()->j + 1] == NULL && data()->r_value == 0) {
        pid = fork();
        if (pid == 0) {
            execve(data()->arg[data()->j][0], data()->arg[data()->j], env);
            exit(0);
        }
        wait(&status);
        return;
    }
}

void exec_and(char **env)
{
    pid_t pid;
    int status;

    while (COND2 && data()->priority[data()->i] != NULL) {
        if (strcmp(data()->priority[data()->i], "&&") != 0)
            break;
        pid = fork();
        if (pid == 0) {
            execve(data()->arg[data()->j][0], data()->arg[data()->j], env);
            exit(0);
        }
        waitpid(pid, &status, 0);
        get_false_return(status);
        if (WEXITSTATUS(status) != 0 && data()->r_value != 0)
            return;
        data()->j++;
        data()->i++;
    }
    exec_and2(env);
    new_exec(env);
}
