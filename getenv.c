#include "my_shell.h"

/**
 * get_my_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **get_my_environ(MyShellInfo *info)
{
    if (!info->my_environ || info->environmentChanged)
    {
        info->my_environ = my_list_to_strings(info->environment);
        info->environmentChanged = 0;
    }

    return info->my_environ;
}

/**
 * my_unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *               constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int my_unset_env(MyShellInfo *info, char *var)
{
    MyList *node = info->environment;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = my_starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->environmentChanged = delete_my_node_at_index(&(info->environment), i);
            i = 0;
            node = info->environment;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->environmentChanged;
}

/**
 * my_set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int my_set_env(MyShellInfo *info, char *var, char *value)
{
    char *buf = NULL;
    MyList *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = (char *)malloc(my_strlen(var) + my_strlen(value) + 2);
    if (!buf)
        return 1;
    my_strcpy(buf, var);
    my_strcat(buf, "=");
    my_strcat(buf, value);
    node = info->environment;
    while (node)
    {
        p = my_starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->environmentChanged = 1;
            return 0;
        }
        node = node->next;
    }
    add_my_node_end(&(info->environment), buf, 0);
    free(buf);
    info->environmentChanged = 1;
    return 0;
}