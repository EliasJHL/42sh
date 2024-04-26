/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** main
*/

#include "include/shell.h"


char **cut_args(char *input)
{
    int i = 0;
    char **array = NULL;
    int nb_words = 0;
    char *token = strdup(input);
    char *tmp = strtok(token, " \t\n");

    while (tmp != NULL) {
        nb_words++;
        tmp = strtok(NULL, " \t\n");
    }
    array = malloc(sizeof(char *) * (nb_words + 1));
    token = strtok(input, " \t\n");
    while (token != NULL) {
        array[i] = strdup(token);
        i++;
        token = strtok(NULL, " \t\n");
    }
    array[i] = NULL;
    return array;
}

/*
void excut_redirection(char **array1, char **array2, char *name, char **env)
{
    int pip[2];
    pid_t pid;
    pid_t pid2;

    pipe(pip);
    pid = fork();
    if (pid == 0) {
        dup2(pip[1], STDIN_FILENO);
        execve(array1[0], array1, env);
    } else {
        close(pip[1]);
        waitpid(pid, NULL, 0);
        pid2 = fork();
        if (pid2 == 0) {
            pip[0] = open(name, O_CREAT | O_APPEND | O_RDWR, 0644);
            dup2(pip[0], STDOUT_FILENO);
            execve(array2[0], array2, env);
        } else {
            close(pip[0]);
            waitpid(pid, NULL, 0);
            exit(EXIT_SUCCESS);
        }
    }
    return;
}*/

//void excut(char **array1, char **array2, char **env)
//{
//    int pip[2];
//    pid_t pid;
//
//    pipe(pip);
//    pid = fork();
//    if (pid == 0) {
//        dup2(pip[1], STDOUT_FILENO);
//        execve(array1[0], array1, env);
//    } else {
//        close(pip[1]);
//        waitpid(pid, NULL, 0);
//        pid = fork();
//        if (pid == 0) {
//            dup2(pip[0], STDOUT_FILENO);
//            execve(array2[0], array2, env);
//        } else {
//            waitpid(pid, NULL, 0);
//            exit(EXIT_SUCCESS);
//        }
//    }
//    return;
//}

void excut(char **array1, char **array2, char **array3, char **env)
{
    int pip[3];
    pid_t pid;

    pipe(pip);
    pid = fork();
    if (pid == 0) {
        dup2(pip[2], STDOUT_FILENO);
        execve(array1[0], array1, env);
    } else {
        close(pip[1]);
        waitpid(pid, NULL, 0);
        pid = fork();
        if (pid == 0) {
            dup2(pip[1], STDOUT_FILENO);
            execve(array2[0], array2, env);
        } else {
            waitpid(pid, NULL, 0);
            pid = fork();
            if (pid == 0) {
                dup2(pip[0], STDIN_FILENO);
                execve(array3[0], array3, env);
            } else {
                waitpid(pid, NULL, 0);
                exit(EXIT_SUCCESS);
            }
        }
    }
    return;
}
/*
void excut(char **array1, char **array2, char **array3, char **env)
{
    int pip[2];
    pid_t pid;

    
    pipe(pip);
    pid = fork();
    if (pid == 0) {
        close(pip[0]);
        if (dup2(pip[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        execve(array1[0], array1, env);
        perror("execve"); 
        exit(EXIT_FAILURE);
    }
    close(pip[1]);
    pid = fork();
    if (pid == 0) {
        close(pip[1]);
        if (dup2(pip[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        execve(array2[0], array2, env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    close(pip[0]);
    wait(NULL);
    wait(NULL);
}

void exec_process(pid_t pid, char **env, char **av1, char **av2)
{
    int pip[2];

    pipe(pip);
    pid = fork();
    if (pid == 0) {
        dup2(pip[1], STDOUT_FILENO);
        execve(av1[0], av1, env);
    } else {
        close(pip[1]);
        waitpid(pid, NULL, 0);
        pid = fork();
        if (pid == 0) {
            dup2(pip[0], STDIN_FILENO);
            execve(av2[0], av2, env);
        } else {
            waitpid(pid, NULL, 0);
            exit(EXIT_SUCCESS);
        }
    }
}*/

int main(int ac, char **av, char **env)
{
    char **array1;
    char **array2;
    char **array3;

    array1 = cut_args(av[1]);
    array2 = cut_args(av[2]);
    array3 = cut_args(av[3]);
    excut(array1, array2, array3, env);
}