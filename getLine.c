#include "my_shell.h"

/**
 * clear_my_info - initializes MyShellInfo struct
 * @info: struct address
 */
void clear_my_info(MyShellInfo *info)
{
    info->argument = NULL;
    info->arguments = NULL;
    info->path = NULL;
    info->argumentCount = 0;
}

/**
 * set_my_info - initializes MyShellInfo struct
 * @info: struct address
 * @av: argument vector
 */
void set_my_info(MyShellInfo *info, char **av)
{
    int i = 0;

    info->fileName = av[0];
    if (info->argument)
    {
        info->arguments = my_strtow(info->argument, " \t");
        if (!info->arguments)
        {
            info->arguments = (char **)malloc(sizeof(char *) * 2);
            if (info->arguments)
            {
                info->arguments[0] = my_strdup(info->argument);
                info->arguments[1] = NULL;
            }
        }
        for (i = 0; info->arguments && info->arguments[i]; i++)
            ;
        info->argumentCount = i;

        replace_my_alias(info);
        replace_my_vars(info);
    }
}

/**
 * free_my_info - frees MyShellInfo struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_my_info(MyShellInfo *info, int all)
{
    my_ffree(info->arguments);
    info->arguments = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->commandBuffer)
            free(info->argument);
        if (info->environment)
            free_my_list(&(info->environment));
        if (info->history)
            free_my_list(&(info->history));
        if (info->alias)
            free_my_list(&(info->alias));
        my_ffree(info->my_environ);
        info->my_environ = NULL;
        my_bfree((void **)info->commandBuffer);
        if (info->readFd > 2)
            close(info->readFd);
        my_putchar(MY_BUF_FLUSH);
    }
}