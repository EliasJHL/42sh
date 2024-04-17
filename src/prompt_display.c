/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** mysh
*/

#include "shell.h"

char *logname_env(void)
{
    if (getenv("USER") != NULL) {
        return getenv("USER");
    } else if (getenv("LOGNAME") != NULL) {
        return getenv("LOGNAME");
    }
    return "root";
}

char *hostname_env(void)
{
    if (getenv("HOST") != NULL)
        return getenv("HOST");
    if (getenv("HOSTNAME") != NULL)
        return getenv("HOSTNAME");
    if (getenv("NAME") != NULL)
        return getenv("NAME");
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

    if (strcmp(getcwd(NULL, 0), getenv("HOME")) == 0)
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