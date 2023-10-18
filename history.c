#include "shell.h"

/**
 * write_my_history - writes history to a file
 * @info: Structure containing potential arguments.
 *
 * Return: 1 on success, else -1
 */
int write_my_history(MyShellInfo *info)
{
    FILE *file;
    MyList *node;

    char *filename = get_my_history_file(info);
    if (!filename)
        return -1;

    file = fopen(filename, "w");
    if (!file)
    {
        free(filename);
        return -1;
    }

    node = info->history;
    while (node)
    {
        fprintf(file, "%s\n", node->str);
        node = node->next;
    }

    fclose(file);
    free(filename);
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
    FILE *file;
    char line[MY_HIST_MAX];
    int linecount = 0;

    char *filename = get_my_history_file(info);
    if (!filename)
        return 0;

    file = fopen(filename, "r");
    if (!file)
    {
        free(filename);
        return 0;
    }

    while (fgets(line, MY_HIST_MAX, file))
    {
        line[strlen(line) - 1] = '\0'; /* Remove newline */
        build_my_history_list(info, line, linecount);
        linecount++;
    }

    fclose(file);
    free(filename);
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
    MyList *node;

    node = add_node_my_end(&(info->history), buf, lineCount);

    return 0;
}
