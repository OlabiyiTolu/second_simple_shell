#include "my_shell.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if info->arguments[0] != "exit"
 */
int my_exit(MyShellInfo *info)
{
    int exitCheck;

    if (info->arguments[1]) /* If there is an exit argument */
    {
        exitCheck = my_atoi(info->arguments[1]);
        if (exitCheck == -1)
        {
            info->status = 2;
            my_puts("Illegal number: ");
            my_puts(info->arguments[1]);
            my_putchar('\n');
            return 1;
        }
        info->errorNumber = my_atoi(info->arguments[1]);
        return -2;
    }
    info->errorNumber = -1;
    return -2;
}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_cd(MyShellInfo *info)
{
    char *s, *dir, buffer[1024];
    int chdirRet;

    s = getcwd(buffer, 1024);
    if (!s)
        my_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->arguments[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdirRet = /* TODO: what should this be? */
                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdirRet = chdir(dir);
    }
    else if (my_strcmp(info->arguments[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            my_puts(s);
            my_putchar('\n');
            return 1;
        }
        my_puts(_getenv(info, "OLDPWD=")), my_putchar('\n');
        chdirRet = /* TODO: what should this be? */
            chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdirRet = chdir(info->arguments[1]);
    if (chdirRet == -1)
    {
        print_error(info, "can't cd to ");
        my_puts(info->arguments[1]), my_putchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * my_help - displays help information for the shell
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_help(MyShellInfo *info)
{
    char **argArray;

    argArray = info->arguments;
    my_puts("Help function not yet implemented.\n");
    if (0)
        my_puts(*argArray); /* Temporary workaround */
    return 0;
}