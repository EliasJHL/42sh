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
#include <fcntl.h>
#include <time.h>
#define COMPARR(a, b) my_strcmp(data()->array[a], b)
#define COND1_EXEC (access(data()->arg[data()->j][0], F_OK) == 0)
#define COND1 (verif(input, history) || COND1_EXEC)
#define COND2 data()->arg[data()->j] != NULL
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
    char ***arg;
    char **priority;
    char **array;
    int *nb_arg_arg;
    int nb_priority;
    int nb_args;
    int i;
    int j;
    int r_value;
    int nfound;
    char *input;
    history_t *history;
    struct env_t *env;
} shell_t;

typedef struct display_s {
    char *logname;
    char *hostname;
} display_t;

void pexecute_history_command(char *input, history_t *history);
int phandle_specific_commands(char *input, history_t *history);
void create_path(char *input, history_t *history);
int execute_command(char **env, char *command);
int search_path(void);
void launch_solo(char *input, history_t *history);
void launch_prio(char *input, history_t *history);
int my_cd(char **input);
int verif_prio(char **input, int j);
void count_arg(void);
int verif_arg(char **input);
void get_false_return(int status);
void exec_and(char **env);
void exec_dpipes(char **env);
void exec_dredir_left(char **env, char **cmd, char *word);
void exec_redir_left(char **env, char **cmd, char *filename);
void exec_cmd(char **env, char **cmd1, char **cmd2);
int separate_priority(void);
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
