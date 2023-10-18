#include "my_shell.h"

int main(int argc, char **argv)
{
    MyShellInfo info = MY_SHELL_INFO_INIT; // Initialize a MyShellInfo struct
    int fd = 2;

    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY); // Attempt to open a file for reading
        if (fd == -1)
        {
            if (errno == EACCES) // Check if the error code is EACCES
                my_exit(&info, 126); // Exit with status 126
            if (errno == ENOENT) // Check if the error code is ENOENT
            {
                my_puts(argv[0]); // Print the program name
                my_puts(": 0: Can't open ");
                my_puts(argv[1]); // Print the filename
                my_putchar('\n'); // Print a newline character
                my_putchar(MY_BUF_FLUSH); // Flush the output buffer
                my_exit(&info, 127); // Exit with status 127
            }
            return EXIT_FAILURE; // Return a failure status
        }
        info.readFd = fd; // Set the read file descriptor
    }
    populate_my_env_list(&info); // Populate the environment list
    read_my_history(&info); // Read command history
    my_shell(&info, argv); // Call the main shell function
    return EXIT_SUCCESS; // Return a success status
}
