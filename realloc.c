#include "shell.h"

/**
 * my_memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The amount of bytes to be filled.
 *
 * Returns: A pointer to the memory area s.
 */
char *my_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++) {
        s[i] = b;
    }
    return s;
}

/**
 * my_ffree - Frees a string array.
 * @arr: The string array to free.
 */
void my_ffree(char **arr)
{
    char **a = arr;

    if (!arr) {
        return;
    }
    while (*arr) {
        free(*arr);
        arr++;
    }
    free(a);
}

/**
 * my_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Returns: Pointer to the reallocated block or NULL on failure.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr) {
        return malloc(new_size);
    }
    if (!new_size) {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size) {
        return ptr;
    }

    p = malloc(new_size);
    if (!p) {
        return NULL;
    }

    old_size = (old_size < new_size) ? old_size : new_size;
    while (old_size--) {
        p[old_size] = ((char *)ptr)[old_size];
    }
    free(ptr);
    return p;
}
