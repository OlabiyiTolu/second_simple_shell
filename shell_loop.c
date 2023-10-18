#include "shell.h"

/**
 * shell_loop - Main shell loop.
 * @info: The parameter and return info struct.
 * @av: The argument vector from main().
 *
 * Returns: 0 on success, 1 on error, or an error code.
 */
int shell_loop(info_t *info, char **av)
{
    ssize_t r = 0;
    int built_in_ret = 0;

    while (r != -1 && built_in_ret != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _mputchar(BUF_FLUSH);
        r = read_input(info);
        if (r != -1)
        {
            set_info(info, av);
            built_in_ret = find_builtin_command(info);
            if (built_in_ret == -1)
                find_executable_command(info);
        }
        else if (interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }
    write_history(info);
    free_info(info, 1);
    if (!interactive(info) && info->status)
        exit(info->status);
    if (built_in_ret == -2)
    {
        if (info->exit_status == -1)
            exit(info->status);
        exit(info->exit_status);
    }
    return built_in_ret;
}

/**
 * find_builtin_command - Find a built-in command.
 * @info: The parameter and return info struct.
 *
 * Returns: -1 if built-in not found, 0 if built-in executed successfully,
 * 1 if built-in found but not successful, -2 if built-in signals exit().
 */
int find_builtin_command(info_t *info)
{
    int i, built_in_ret = -1;
    MyBuiltInTable built_in_table[] = {
        {"exit", _exit_shell},
        {"env", _print_environment},
        {"help", _show_help},
        {"history", _show_history},
        {"setenv", _set_environment_variable},
        {"unsetenv", _unset_environment_variable},
        {"cd", _change_directory},
        {"alias", _manage_alias},
        {NULL, NULL}};

    for (i = 0; built_in_table[i].command; i++)
    {
        if (_strcmp(info->argv[0], built_in_table[i].command) == 0)
        {
            info->line_count++;
            built_in_ret = built_in_table[i].function(info);
            break;
        }
    }
    return built_in_ret;
}

/**
 * find_executable_command - Find an executable command in PATH.
 * @info: The parameter and return info struct.
 *
 * Returns: void.
 */
void find_executable_command(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->line_count_flag == 1)
    {
        info->line_count++;
        info->line_count_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!_is_delimiter(info->arg[i], " \t\n"))
        {
            k++;
        }
    }
    if (!k)
        return;

    path = find_command_in_path(info, _get_environment_variable(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        execute_command(info);
    }
    else
    {
        if ((interactive(info) || _get_environment_variable(info, "PATH=") || info->argv[0][0] == '/') && is_executable_command(info, info->argv[0]))
        {
            execute_command(info);
        }
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error_message(info, "not found\n");
        }
    }
}

/**
 * execute_command - Forks a new process to run the command.
 * @info: The parameter and return info struct.
 *
 * Returns: void.
 */
void execute_command(info_t *info)
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
        if (execute_process(info) == -1)
        {
            free_info(info, 1);
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
                print_error_message(info, "Permission denied\n");
        }
    }
}
