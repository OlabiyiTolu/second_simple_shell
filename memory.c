#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr) // Check if the pointer and its value are not NULL
    {
        free(*ptr);  // Free the memory pointed to by the pointer
        *ptr = NULL; // Set the pointer to NULL
        return (1);   // Return 1 to indicate successful freeing
    }
    return (0); // Return 0 to indicate that no freeing was performed
}