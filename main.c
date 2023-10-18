#include "shell.h"

int main(int argc, char **argv)
{
    MyShellInfo info;
    int fd = 2;  // Move the declaration here
    info.commandBuffer = NULL;

    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" ((int)fd)
        : "r" (fd)
    );

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                my_exit(&info);
            if (errno == ENOENT)
            {
                my_puts(argv[0]);
                my_puts(": 0: Can't open ");
                my_puts(argv[1]);
                my_putchar('\n');
                my_putchar(MY_BUF_FLUSH);
                my_exit(&info);
            }
            return EXIT_FAILURE;
        }
        info.readFd = fd;
    }

    info.commandBuffer = malloc(sizeof(char *) * 10);

    populate_my_env_list(&info);
    read_my_history(&info);
    my_shell(&info, argv);
    return EXIT_SUCCESS;
}
