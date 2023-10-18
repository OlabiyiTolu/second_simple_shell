#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info[] = {INFO_INIT}; // Initialize an array of info_t structs
    int fd = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY); // Attempt to open a file for reading
        if (fd == -1)
        {
            if (errno == EACCES) // Check if the error code is EACCES
                exit(126); // Exit with status 126
            if (errno == ENOENT) // Check if the error code is ENOENT
            {
                _mputs(av[0]); // Print the program name
                _mputs(": 0: Can't open ");
                _mputs(av[1]); // Print the filename
                _mputchar('\n'); // Print a newline character
                _mputchar(BUF_FLUSH); // Flush the output buffer
                exit(127); // Exit with status 127
            }
            return (EXIT_FAILURE); // Return a failure status
        }
        info->readfd = fd; // Set the read file descriptor
    }
    populate_env_list(info); // Populate the environment list
    read_history(info); // Read command history
    hsh(info, av); // Call the main shell function
    return (EXIT_SUCCESS); // Return a success status
}