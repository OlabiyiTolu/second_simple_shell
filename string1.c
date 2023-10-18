#include "shell.h"

/**
 * my_strcpy - Copies a string from source to destination.
 * @dst: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *my_strcpy(char *dst, char *src)
{
    int i = 0;

    if (dst == src || src == NULL)
        return dst;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

/**
 * my_strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string or NULL on failure.
 */
char *my_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return NULL;
    for (length++; length--;)
        ret[length] = *--str;
    return ret;
}

/**
 * my_puts - Prints an input string to the standard output.
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
 * my_putchar - Writes a character to the standard output.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
    static int i;
    static char buf[MY_WRITE_BUF_SIZE];

    if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != MY_BUF_FLUSH)
        buf[i++] = c;
    return 1;
}