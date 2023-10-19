#include "shell.h"

/**
 * my_puts - Print an input string to standard output.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
 
void my_puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        my_putchar(str[i]);
        i++;
    }
}

/**
 * my_putchar - Write a character to the standard error stream.
 * @c: The character to print.
 *
 * Return: On success, return 1. On error, return -1, and set errno appropriately.
 */

int my_putchar(char c)
{
    static int i;
    static char buf[MY_WRITE_BUF_SIZE];

    if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != MY_BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * put_fd - Write a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, return 1. On error, return -1, and set errno appropriately.
 */

int put_fd(char c, int fd)
{
    static int i;
    static char buf[MY_WRITE_BUF_SIZE];

    if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != MY_BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * puts_fd - Print an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */

int puts_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;
    while (*str)
    {
        i += put_fd(*str++, fd);
    }
    return i;
}
