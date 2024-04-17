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

typedef struct env_t {
    char *vname;
    char *vcontent;
    struct env_t *next;
} env_t;

typedef struct alias_t {
    char *alias;
    char **command;
    int nb_command;
    struct alias_t *next;
} alias_t;

typedef struct shell_s {
    char **array;
    char ***pipe;
    int nb_pipe;
    int nb_args;
    struct env_t *env;
    struct alias_t *alias;
} shell_t;

void check_alias(void);
int unalias(void);
void remove_a(alias_t **alias, char *name);
void adding_a(alias_t **alias, char *name);
int disp_a(alias_t *alias);
void clear_a(alias_t *alias);
int aliases(void);
void separate_pipe(void);
void separate_command(char *arg);
int mini_printf(const char *format, ...);
char *my_strncpy(char *dest, char const *src, int n);
int my_strcmp(char const *s1, char const *s2);
shell_t *data(void);
int my_strlen(char const *str);
void command(char *input);
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
