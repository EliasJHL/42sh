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

void excut_redirection(char **array1, char **array2, char **env)
{
    int pip[2];
    pid_t pid;

    pipe(pip);
    pid = fork();
    if (pid == 0) {
        dup2(pip[1], STDIN_FILENO);
        execve(array1[0], array1, env);
    } else {
        close(pip[1]);
        waitpid(pid, NULL, 0);
        pid = fork();
        if (pid == 0) {
            dup2(pip[0], STDOUT_FILENO);
            execve(array2[0], array2, env);
        } else {
            close(pip[0]);
            waitpid(pid, NULL, 0);
            exit(EXIT_SUCCESS);
        }
    }
    return;
}

int main(int ac, char **av, char **env)
{
    if (ac == 3) {
        char **array1 = cut_args(av[1]);
        char **array2 = cut_args(av[2]);
        excut_redirection(array1, array2, env);
    } else {
        printf("Usage: ./mysh 'command1' 'command2'\n");
        return 84;
    }
}