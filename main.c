#include "shell.h"

int main(int argc, char **argv)
{
    MyShellInfo info = MY_SHELL_INFO_INIT; 
    int fd = 2;

    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY); 
        if (fd == -1)
        {
            if (errno == EACCES) 
                my_exit(&info, 126); 
            if (errno == ENOENT) 
            {
                my_puts(argv[0]);
                my_puts(": 0: Can't open ");
                my_puts(argv[1]);
                my_putchar('\n');
                my_putchar(MY_BUF_FLUSH);
                my_exit(&info, 127);
            }
            return EXIT_FAILURE;
        }
        info.readFd = fd;
    }
    populate_my_env_list(&info);
    read_my_history(&info);
    my_shell(&info, argv);
    return EXIT_SUCCESS;
}
