#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **av)
{
    ssize_t r = 0;
    int MyBuiltIn_ret = 0;

    while (r != -1 && MyBuiltIn_ret != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _mputchar(BUF_FLUSH);
        r = read_input(info);
        if (r != -1)
        {
            set_info(info, av);
            MyBuiltIn_ret = find_builtin_command(info);
            if (builtin_ret == -1)
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
    if (builtin_ret == -2)
    {
        if (info->exit_status == -1)
            exit(info->status);
        exit(info->exit_status);
    }
    return (builtin_ret);
}

/**
 * find_builtin_command - finds a MyBuiltIn command
 * @info: the parameter & return info struct
 *
 * Return: -1 if MyBuiltIn not found,
 *         0 if MyBuiltIn executed successfully,
 *         1 if MyBuiltIn found but not successful,
 *         -2 if MyBuiltIn signals exit()
 */
int find_builtin_command(info_t *info)
{
    int i, built_in_ret = -1;
    MyBuiltInTable MyBuiltIntbl[] = {
        {"exit", _exit_shell},
        {"env", _print_environment},
        {"help", _show_help},
        {"history", _show_history},
        {"setenv", _set_environment_variable},
        {"unsetenv", _unset_environment_variable},
        {"cd", _change_directory},
        {"alias", _manage_alias},
        {NULL, NULL}};

    for (i = 0; MyBuiltIntbl[i].command; i++)
    {
        if (_strcmp(info->argv[0], MyBuiltIntbl[i].command) == 0)
        {
            info->line_count++;
            built_in_ret = MyBuiltIntbl[i].function(info);
            break;
        }
    }
    return built_in_ret;
}

/**
 * find_executable_command - finds an executable command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
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
 * execute_command - forks a new process to run the command
 * @info: the parameter & return info struct
 *
 * Return: void
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