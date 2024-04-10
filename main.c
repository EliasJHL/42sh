/*
** EPITECH PROJECT, 2023
** Elias josué HAJJAR LLAUQUEN
** File description:
** project for epitech
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int i;
    char *str = malloc(sizeof(char) * 1000);
    str = strdup("Hello World !\n");
    write(1, str, strlen(str));
    printf("i = %d\n", i);
    return 0;
}
