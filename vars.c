#include "shell.h"

/**
 * my_is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_my_chain(MyShellInfo *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->commandBufferType = MY_CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->commandBufferType = MY_CMD_AND;
    }
    else if (buf[j] == ';') /* found end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        info->commandBufferType = MY_CMD_CHAIN;
    }
    else
        return 0;
    *p = j;
    return 1;
}

/**
 * my_check_chain - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_my_chain(MyShellInfo *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->commandBufferType == MY_CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->commandBufferType == MY_CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * my_replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_my_alias(MyShellInfo *info)
{
    int i;
    MyList *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = my_node_starts_with(info->alias, info->arguments[0], '=');
        if (!node)
            return 0;
        free(info->arguments[0]);
        p = my_strchr(node->str, '=');
        if (!p)
            return 0;
        p = my_strdup(p + 1);
        if (!p)
            return 0;
        info->arguments[0] = p;
    }
    return 1;
}

/**
 * my_replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_my_vars(MyShellInfo *info)
{
    int i = 0;
    MyList *node;

    for (i = 0; info->arguments[i]; i++)
    {
        if (info->arguments[i][0] != '$' || !info->arguments[i][1])
            continue;

        if (!my_strcmp(info->arguments[i], "$?"))
        {
            replace_my_string(&(info->arguments[i]), my_strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!my_strcmp(info->arguments[i], "$$"))
        {
            replace_my_string(&(info->arguments[i]), my_strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = my_node_starts_with(info->environment, &info->arguments[i][1], '=');
        if (node)
        {
            replace_my_string(&(info->arguments[i]), my_strdup(my_strchr(node->str, '=') + 1));
            continue;
        }
        replace_my_string(&info->arguments[i], my_strdup(""));
    }
    return 0;
}

/**
 * my_replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_my_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
