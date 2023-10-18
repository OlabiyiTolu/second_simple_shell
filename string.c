#include "shell.h"

/**
 * my_strlen - Get the length of a string.
 * @s: The string to check.
 *
 * Returns: The integer length of the string.
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
 * my_strcmp - Perform a lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Returns: A negative value if s1 < s2, a positive value if s1 > s2, or zero if s1 == s2.
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

    return (*s1 - *s2);
}

/**
 * my_starts_with - Check if a string starts with a specific prefix.
 * @string: The string to search.
 * @prefix: The prefix to find.
 *
 * Returns: The address of the character after the prefix in the string or NULL.
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
 * my_strcat - Concatenate two strings.
 * @destination: The destination buffer.
 * @source: The source buffer.
 *
 * Returns: A pointer to the destination buffer.
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
