#include "shell.h"

/**
 * my_shell_loop - Main shell loop.
 * @info: The parameter and return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int my_shell_loop(MyShellInfo *info, char **av)
{
    ssize_t r = 0;
    int built_in_ret = 0;

    while (r != -1 && built_in_ret != -2)
    {
        clear_my_info(info);
        if (my_interact(info))
            my_puts("$ ");
        my_putchar(MY_BUF_FLUSH);
        r = my_get_input(info);
        if (r != -1)
        {
            set_my_info(info, av);
            built_in_ret = find_my_built_in(info);
            if (built_in_ret == -1)
                find_my_command(info);
        }
        else if (my_interact(info))
            my_putchar('\n');
        free_my_info(info, 0);
    }
    write_my_history(info);
    free_my_info(info, 1);
    if (!my_interact(info) && info->status)
        exit(info->status);
    if (built_in_ret == -2)
    {
        if (info->errorNumber == -1)
            exit(info->status);
        exit(info->errorNumber);
    }
    return built_in_ret;
}

/**
 * find_my_built_in - Find a built-in command.
 * @info: The parameter and return info struct.
 *
 * Return: -1 if built-in not found, 0 if built-in executed successfully,
 * 1 if built-in found but not successful, -2 if built-in signals exit().
 */
int find_my_built_in(MyShellInfo *info)
{
    int i, built_in_ret = -1;
    MyBuiltInTable built_in_table[] = {
        {"exit", my_exit},
        {"env", my_env},
        {"help", my_help},
        {"history", my_history},
        {"setenv", my_mset_env},
        {"unsetenv", my_munset_env},
        {"cd", my_cd},
        {"alias", my_alias},
        {NULL, NULL}
    };

    for (i = 0; built_in_table[i].type; i++)
    {
        if (my_strcmp(info->arguments[0], built_in_table[i].type) == 0)
        {
            info->lineCount++;
            built_in_ret = built_in_table[i].function(info);
            break;
        }
    }
    return built_in_ret;
}

/**
 * find_my_command - Find an executable command in PATH.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void find_my_command(MyShellInfo *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->arguments[0];
    if (info->lineCountFlag == 1)
    {
        info->lineCount++;
        info->lineCountFlag = 0;
    }
    for (i = 0, k = 0; info->argument[i]; i++)
    {
        if (!is_delimiter(info->argument[i], " \t\n"))
        {
            k++;
        }
    }
    if (!k)
        return;

    path = find_my_path(info, _getenv(info, "PATH="), info->arguments[0]);
    if (path)
    {
        info->path = path;
        fork_my_command(info);
    }
    else
    {
        if ((my_interact(info) || _getenv(info, "PATH=") || info->arguments[0][0] == '/') && is_my_command(info, info->arguments[0]))
        {
            fork_my_command(info);
        }
        else if (*(info->argument) != '\n')
        {
            info->status = 127;
            print_my_error(info, "not found\n");
        }
    }
}

/**
 * fork_my_command - Forks a new process to run the command.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void fork_my_command(MyShellInfo *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->arguments, info->my_environ) == -1)
        {
            free_my_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_my_error(info, "Permission denied\n");
        }
    }
}
