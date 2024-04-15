/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** mini_printf
*/

#include <stdarg.h>
#include <unistd.h>

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        write(1, &str[i], 1);
        i++;
    }
    return 0;
}

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i = i + 1;
    }
    return i;
}

int my_putnbr(int nb)
{
    int a;

    if (nb < 0) {
        nb = nb * (-1);
        write(1, "-", 1);
    }
    if (nb >= 10){
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    } else {
        a = 48 + nb % 10;
        write(1, &a, 1);
    }
    return 0;
}

int verification(const char *format, int i, va_list ap)
{
    char c;

    if (format[i + 1] == 's') {
        my_putstr(va_arg(ap, char *));
    }
    if (format[i + 1] == 'd') {
        my_putnbr(va_arg(ap, int));
    }
    if (format[i + 1] == 'i') {
        my_putnbr(va_arg(ap, int));
    }
    if (format[i + 1] == 'c') {
        c = va_arg(ap, int);
        write(1, &c, 1);
    }
    if (format[i + 1] == '%') {
        write(1, "%%", 1);
    }
    return 0;
}

int mini_printf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            verification(format, i, ap);
            i++;
        } else {
            write(1, &format[i], 1);
        }
    }
    return 0;
}
