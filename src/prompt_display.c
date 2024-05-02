/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

char *logname_env(void)
{
    if (my_strcmp(my_getenv(data()->env, "USERNAME"), "HOME") != 0) {
        return my_getenv(data()->env, "USER");
    } else if (my_strcmp(my_getenv(data()->env, "LOGNAME"), "HOME") != 0) {
        return my_getenv(data()->env, "LOGNAME");
    }
    return "root";
}

char *hostname_env(void)
{
    if (my_strcmp(my_getenv(data()->env, "NAME"), "HOME") != 0)
        return my_getenv(data()->env, "NAME");
    if (my_strcmp(my_getenv(data()->env, "HOST"), "HOME") != 0)
        return my_getenv(data()->env, "HOST");
    if (my_strcmp(my_getenv(data()->env, "HOSTNAME"), "HOME") != 0)
        return my_getenv(data()->env, "HOSTNAME");
    return "root";
}

display_t *stock_display(void)
{
    display_t *display = malloc(sizeof(display_t));

    display->logname = strdup(logname_env());
    display->hostname = strdup(hostname_env());
    return display;
}

int command_line_display(display_t *display)
{
    char *pwd = NULL;
    char *home_path = my_getenv(data()->env, "HOME");

    if (strcmp(getcwd(NULL, 0), home_path) == 0)
        pwd = strdup("~");
    else
        pwd = getcwd(NULL, 0);
    printf("%s@%s:%s$ ", display->logname, display->hostname, pwd);
    free(pwd);
    free(display->logname);
    free(display->hostname);
    free(display);
    return 0;
}
