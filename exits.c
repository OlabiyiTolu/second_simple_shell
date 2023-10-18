#include "shell.h"

/**
 * my_strncpy - Copies a string with a specified length.
 * @dst: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: A pointer to the destination string.
 */
char *my_strncpy(char *dst, const char *src, int n) {
    char *original_dst = dst;

    while (n > 0 && (*dst++ = *src++)) {
        n--;
    }

    if (n > 0) {
        while (--n > 0) {
            *dst++ = '\0';
        }
    }

    return original_dst;
}

/**
 * my_strncat - Concatenates two strings with a specified length.
 * @dst: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 * Return: A pointer to the destination string.
 */
char *my_strncat(char *dst, const char *src, int n) {
    char *original_dst = dst;

    while (*dst != '\0') {
        dst++;
    }

    while (n > 0 && (*dst++ = *src++)) {
        n--;
    }

    if (n > 0) {
        *dst = '\0';
    }

    return original_dst;
}

/**
 * my_strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of the character or NULL if not found.
 */
char *my_strchr(const char *s, int c) {
    while (*s) {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }

    return NULL;
}
