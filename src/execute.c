/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

void exec_redir_right(char **env, char **cmd, char *filename)
{
    int fd;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execve(cmd[0], cmd, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}

void exec_dredir_right(char **env, char **cmd, char *filename)
{
    int fd;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execve(cmd[0], cmd, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}

static void prog1(int fd[2], char **env, char **cmd1)
{
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    if (verif_prio(cmd1, data()->j - 1))
        exit(0);
    execve(cmd1[0], cmd1, env);
    exit(0);
}

static void prog2(int fd[2], char **env, char **cmd2)
{
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    if (data()->arg[data()->j + 1] == NULL) {
        if (verif_prio(cmd2, data()->j - 1))
            exit(0);
        execve(cmd2[0], cmd2, env);
        exit(0);
    } else {
        exec_cmd(env, cmd2, data()->arg[data()->j + 1]);
        exit(0);
    }
}

void exec_pipe_proc(int *fd, pid_t pid2, int status)
{
    close(fd[0]);
    close(fd[1]);
    waitpid(pid2, &status, 0);
}

void exec_pipe(char **env, char **cmd1, char **cmd2)
{
    int fd[2];
    pid_t pid1;
    pid_t pid2;
    int status;

    data()->j++;
    data()->i++;
    pipe(fd);
    pid1 = fork();
    if (pid1 == 0){
        prog1(fd, env, cmd1);
    } else {
        waitpid(pid1, &status, 0);
        get_false_return(status);
        pid2 = fork();
        if (pid2 == 0){
            prog2(fd, env, cmd2);
        }
    }
    exec_pipe_proc(fd, pid2, status);
}

static void exec_cmd2(char **env, char **cmd1, char **cmd2)
{
    if (strcmp(data()->priority[data()->i], "<") == 0) {
        exec_redir_left(env, cmd1, cmd2[0]);
        return;
    }
    if (strcmp(data()->priority[data()->i], "<<") == 0) {
        exec_dredir_left(env, cmd1, cmd2[0]);
        return;
    }
    if (strcmp(data()->priority[data()->i], "||") == 0) {
        exec_dpipes(env);
        return;
    }
    if (strcmp(data()->priority[data()->i], "&&") == 0) {
        exec_and(env);
        return;
    }
    return;
}

void exec_cmd(char **env, char **cmd1, char **cmd2)
{
    if (data()->i >= data()->nb_priority)
        return;
    if (strcmp(data()->priority[data()->i], "|") == 0) {
        exec_pipe(env, cmd1, cmd2);
        return;
    }
    if (strcmp(data()->priority[data()->i], ">") == 0) {
        exec_redir_right(env, cmd1, cmd2[0]);
        return;
    }
    if (strcmp(data()->priority[data()->i], ">>") == 0) {
        exec_dredir_right(env, cmd1, cmd2[0]);
        return;
    }
    exec_cmd2(env, cmd1, cmd2);
    return;
}
