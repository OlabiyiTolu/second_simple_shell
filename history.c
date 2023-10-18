#include "my_shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing the history file
 */
char *get_history_file(MyShellInfo *info)
{
    char *buf, *dir;

    dir = _getenv(info, "HOME=");
    if (!dir)
        return NULL;
    buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(MY_HIST_FILE) + 2));
    if (!buf)
        return NULL;
    buf[0] = 0;
    my_strcpy(buf, dir);
    my_strcat(buf, "/");
    my_strcat(buf, MY_HIST_FILE);
    return buf;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(MyShellInfo *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    MyList *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return -1;
    for (node = info->history; node; node = node->next)
    {
        my_puts_fd(node->str, fd);
        my_put_fd('\n', fd);
    }
    my_put_fd(MY_BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * read_history - reads history from a file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(MyShellInfo *info)
{
    int i, last = 0, lineCount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;
    if (!fstat(fd, &st))
        fsize = st.st_size;
    if (fsize < 2)
        return 0;
    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return 0;
    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;
    if (rdlen <= 0)
        return free(buf), 0;
    close(fd);
    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            build_history_list(info, buf + last, lineCount++);
            last = i + 1;
        }
    if (last != i)
        build_history_list(info, buf + last, lineCount++);
    free(buf);
    info->historyCount = lineCount;
    while (info->historyCount-- >= MY_HIST_MAX)
        delete_my_node_at_index(&(info->history), 0);
    renumber_history(info);
    return info->historyCount;
}

/**
 * build_history_list - adds an entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @lineCount: the history line count, historyCount
 *
 * Return: Always 0
 */
int build_history_list(MyShellInfo *info, char *buf, int lineCount)
{
    MyList *node = NULL;

    if (info->history)
        node = info->history;
    add_my_node_end(&node, buf, lineCount);

    if (!info->history)
        info->history = node;
    return 0;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new historyCount
 */
int renumber_history(MyShellInfo *info)
{
    MyList *node = info->history;
    int i = 0;

    while (node)
    {
        node->number = i++;
        node = node->next;
    }
    return info->historyCount = i;
}
