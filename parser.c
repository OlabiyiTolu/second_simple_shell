#include "shell.h"

/**
 * Parsing, syntax analysis, or syntactic analysis is the process of analyzing a string of symbols,
 * either in natural language, computer languages, or data structures.
 */

/**
 * is_executable_command - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable_command(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicate_characters - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to a new buffer
 */
char *duplicate_characters(char *path_str, int start, int stop)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (path_str[i] != ':')
            buffer[k++] = path_str[i];
    buffer[k] = 0;
    return buffer;
}

/**
 * find_command_in_path - finds this command in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_command_in_path(info_t *info, char *path_str, char *command)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!path_str)
        return NULL;
    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_executable_command(info, command))
            return command;
    }
    while (1)
    {
        if (!path_str[i] || path_str[i] == ':')
        {
            path = duplicate_characters(path_str, curr_pos, i);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (is_executable_command(info, path))
                return path;
            if (!path_str[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}