#include "shell.h"

/**
 * _string_copy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to the destination
 */
char *_string_copy(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == 0)
        return destination;
    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = 0;
    return destination;
}

/**
 * _string_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_string_duplicate(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return NULL;
    while (*str++)
        length++;
    result = malloc(sizeof(char) * (length + 1));
    if (!result)
        return NULL;
    for (length++; length--;)
        result[length] = *--str;
    return result;
}

/**
 * _string_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _string_puts(char *str)
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
 * _string_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _string_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}