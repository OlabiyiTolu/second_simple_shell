#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;
    return s;
}

/**
 * free_string_array - frees a string array
 * @arr: the string array to free
 */
void free_string_array(char **arr)
{
    char **a = arr;

    if (!arr)
        return;
    while (*arr)
        free(*arr++);
    free(a);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the reallocated block or NULL on failure
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return p;
}