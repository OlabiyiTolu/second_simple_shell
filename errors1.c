#include "shell.h"

/**
 * my_error_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 *       -1 on error
 */
int my_error_atoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }
    return result;
}

/**
 * print_my_error - prints an error message
 * @info: the MyShellInfo struct
 * @estr: string containing the specified error type
 *
 * Return: void
 */
void print_my_error(MyShellInfo *info, char *estr)
{
    my_puts(info->fileName);
    my_puts(": ");
    print_decimal(info->lineCount, STDERR_FILENO);
    my_puts(": ");
    my_puts(info->arguments[0]);
    my_puts(": ");
    my_puts(estr);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
    int (*my_putchar)(char) = my_putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        my_putchar = my_putchar;
    if (input < 0)
    {
        _abs_ = -input;
        my_putchar('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            my_putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    my_putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_number - converter function, similar to itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & MY_CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & MY_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
