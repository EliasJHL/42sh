/*
** EPITECH PROJECT, 2024
** shell
** File description:
** shell
*/

#include <glob.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#define COMPARR(a, b) my_strcmp(data()->array[a], b)
#pragma once

typedef struct env_t {
    char *vname;
    char *vcontent;
    struct env_t *next;
} env_t;

typedef struct history_s {
    char *command;
    time_t time;
    struct history_s *next;
} history_t;

typedef struct shell_s {
    char **array;
    char ***pipe;
    int nb_pipe;
    int nb_args;
    struct env_t *env;
} shell_t;

typedef struct display_s {
    char *logname;
    char *hostname;
} display_t;

void separate_pipe(void);
void separate_command(char *arg, history_t *history);
int mini_printf(const char *format, ...);
char *my_strncpy(char *dest, char const *src, int n);
int my_strcmp(char const *s1, char const *s2);
shell_t *data(void);
int my_strlen(char const *str);
void execute_command_if_exists(char *command, char **env);
void command(char *input, history_t *history);
void handle_history_command(history_t *history, char *arg);
void separate_arg(char *arg);
void free_func(char **array, int nb);
char *my_strdup(char *str);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_getenv(env_t *env, char *vname);
void my_strskipcpy(char *dest, const char *src, int skip);
int my_setenv(env_t **env, char *vname, char *vcontent);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, const char *src);
void my_unsetenv(env_t **env, char *vname);
void add(env_t **env, char *vname, char *vcontent);
int disp(env_t *env);
void clear(env_t *env);
char **array_env(env_t *env);
int is_number(char c);
int is_letter(char c);
display_t *stock_display(void);
int command_line_display(display_t *display);
void print_history(history_t *history);
int add_history(history_t **history, char *command);
void print_commands_from(history_t *start, int nbr);
void print_history2(history_t *history, int nbr);
history_t *get_command_by_number(history_t *history, int nbr);
void execute_last_command(history_t *history);
void handle_history_command(history_t *history, char *arg);
void execute_command_by_number(char *input, history_t *history);
void execute_history_command(char *input, history_t *history);
int check_etoile(char *str);
void globbing_part1(char *str);
int my_getnbr(char const *str);
int handle_specific_commands(char *input, history_t *history);
