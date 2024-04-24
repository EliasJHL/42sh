/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** cd .c
*/
#include "shell.h"

static int my_cd2(void)
{
    char cwd[1024];

    if (data()->nb_args == 1){
        if (chdir(data()->array[1]) == -1) {
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

    if (data()->nb_args > 1) {
        mini_printf("cd: too many arguments\n");
        return 1;
    }
    if (data()->nb_args == 0) {
        my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
        chdir(my_getenv(data()->env, "HOME"));
        my_setenv(&data()->env, "PWD", my_getenv(data()->env, "HOME"));
        return 1;
    }
    if (my_strcmp(data()->array[1], "-") == 0) {
        chdir(my_getenv(data()->env, "OLDPWD"));
        my_setenv(&data()->env, "OLDPWD", my_getenv(data()->env, "PWD"));
        my_setenv(&data()->env, "PWD", getcwd(cwd, sizeof(cwd)));
        return 1;
    }
    return my_cd2();
}
