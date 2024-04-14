/*
** EPITECH PROJECT, 2023
** Elias josué HAJJAR LLAUQUEN
** File description:
** project for epitech
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *token = NULL;
    size_t len = 0;

    while (1) {
        if (getline(&token, &len, stdin) == -1) {
            free(token);
            return 0;
        }
        if (strcmp(token, "exit\n") == 0) {
            free(token);
            return 0;
        }
        printf("%s", token);    
    }
    free(token);
    return 0;
}
