/*
** EPITECH PROJECT, 2024
** shell
** File description:
** shell
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

#define COMPARR(a, b) my_strcmp(data()->array[a], b)

#pragma once

typedef struct list_commad_s {
    char **command_a;
    struct list_commad_s *next;
} list_command_t;

typedef struct input_s {
    char *seg;
    struct input_s *next;
} input_t;

typedef struct env_t {
    char *vname;
    char *vcontent;
    struct env_t *next;
} env_t;

typedef struct shell_s {
    char **array;
    char ***pipe;
    int nb_pipe;
    int nb_args;
    struct list_commad_s *command;
    struct input_s *input;
    struct env_t *env;
} shell_t;

void separate_pipe(void);
void separate_command(char *arg);
int mini_printf(const char *format, ...);
char *my_strncpy(char *dest, char const *src, int n);
int my_strcmp(char const *s1, char const *s2);
shell_t *data(void);
int my_strlen(char const *str);
int command(void);
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
int parsing(char *buffer);
char **my_copy_array(char **array);
void my_freearray(char **array);
int my_arraycmp(char **array1, char **array2);
void parsing_command(void);
int my_arraylen(char **array);
int my_cd(void);

/* list_input */
void addback_input(input_t **head, char *str);
void delall_input(input_t *head);
void print_list_input(input_t *head);
void delteindex_input(input_t **head, char *index);
/* list_input */

/* list_command */
void addback_command(list_command_t **head, char **array);
void delall_commmand(list_command_t *head);
void delteindex_command(list_command_t **head, char **index);
void print_list_command(list_command_t *head);
/* list_command */
