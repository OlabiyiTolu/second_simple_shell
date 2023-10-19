#include "shell.h"

/**
 * my_bfree - Frees a pointer and sets its address to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, 0 otherwise.
 */
int my_bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
