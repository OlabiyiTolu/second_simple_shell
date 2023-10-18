#include "shell.h"

/**
 * my_strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of the string
 */
int my_strlen(char *s)
{
    int length = 0;

    if (!s)
        return 0;

    while (*s++)
        length++;
    return length;
}

/**
 * my_strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int my_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * my_starts_with - checks if a string starts with a specific prefix
 * @string: the string to search
 * @prefix: the prefix to find
 *
 * Return: address of the character after the prefix in the string or NULL
 */
char *my_starts_with(const char *string, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix++ != *string++)
            return NULL;
    }
    return (char *)string;
}

/**
 * my_strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *my_strcat(char *destination, char *source)
{
    char *result = destination;

    while (*destination)
    {
        destination++;
    }
    while (*source)
    {
        *destination++ = *source++;
    }
    *destination = *source;
    return result;
}