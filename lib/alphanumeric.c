/*
** EPITECH PROJECT, 2024
** alphanumeric
** File description:
** alphanumeric
*/

int is_number(char c)
{
    if (c >= 48 && c <= 57)
        return 1;
    return 0;
}

int is_letter(char c)
{
    if (c >= 65 && c <= 90)
        return 1;
    if (c >= 97 && c <= 122)
        return 1;
    return 0;
}
