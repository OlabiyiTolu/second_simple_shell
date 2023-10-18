#include "shell.h"

/**
 * get_my_history_file - gets the history file
 * @info: Structure containing potential arguments.
 *
 * Return: Allocated string containing history file.
 */
char *get_my_history_file(MyShellInfo *info)
{
    char *dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;

    char *filename = malloc(sizeof(char) * (strlen(dir) + strlen(MY_HIST_FILE) + 2));
    if (!filename)
        return NULL;

    strcpy(filename, dir);
    strcat(filename, "/");
    strcat(filename, MY_HIST_FILE);

    return filename;
}

/**
 * write_my_history - writes history to a file
 * @info: Structure containing potential arguments.
 *
 * Return: 1 on success, else -1
 */
int write_my_history(MyShellInfo *info)
{
    char *filename = get_my_history_file(info);
    if (!filename)
        return -1;

    FILE *file = fopen(filename, "w");
    free(filename);

    if (!file)
        return -1;

    MyList *node = info->history;
    while (node)
    {
        fprintf(file, "%s\n", node->str);
        node = node->next;
    }

    fclose(file);
    return 1;
}

/**
 * read_my_history - reads history from a file
 * @info: Structure containing potential arguments.
 *
 * Return: histcount on success, 0 otherwise
 */
int read_my_history(MyShellInfo *info)
{
    char *filename = get_my_history_file(info);
    if (!filename)
        return 0;

    FILE *file = fopen(filename, "r");
    free(filename);

    if (!file)
        return 0;

    char line[MY_HIST_MAX];
    int linecount = 0;

    while (fgets(line, MY_HIST_MAX, file))
    {
        line[strlen(line) - 1] = '\0'; // Remove newline
        build_my_history_list(info, line, linecount);
        linecount++;
    }

    fclose(file);
    return linecount;
}

/**
 * build_my_history_list - adds an entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: Buffer
 * @lineCount: History line count
 *
 * Return: 0 on success
 */
int build_my_history_list(MyShellInfo *info, char *buf, int lineCount)
{
    add_node_end(&(info->history), buf, lineCount);
    return 0;
}

/**
 * renumber_my_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 *
 * Return: The new histcount
 */
int renumber_my_history(MyShellInfo *info)
{
    MyList *node = info->history;
    int lineCount = 0;

    while (node)
    {
        node->num = lineCount++;
        node = node->next;
    }

    info->histcount = lineCount;
    return lineCount;
}