#include "shell.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @dst: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dst, char *src)
{
    int i = 0;

    if (dst == src || src == 0)
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
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string or NULL on failure.
 */
char *_strdup(const char *str)
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
 * _puts - Prints an input string to the standard output.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _putchar - Writes a character to the standard output.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != MY_BUF_FLUSH)
        buf[i++] = c;
    return 1;
}