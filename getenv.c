#include "shell.h"

/**
 * get_my_environ - Return a copy of the environment variables.
 * @info: Pointer to the struct containing potential arguments.
 *
 * Return: A copy of the environment variables.
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
 * my_unset_env - Removes an environment variable.
 * @info: Pointer to the struct containing potential arguments.
 * @var: The name of the environment variable to be removed.
 *
 * Return: 1 on successful removal, 0 otherwise.
 */

int my_unset_env(MyShellInfo *info, char *var)
{
    MyList *node = info->environment;
    size_t index = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = my_starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->environmentChanged = delete_my_node_at_index(&(info->environment), index);
            index = 0;
            node = info->environment;
            continue;
        }
        node = node->next;
        index++;
    }

    return info->environmentChanged;
}

/**
 * my_set_env - Initializes or modifies an environment variable.
 * @info: Pointer to the struct containing potential arguments.
 * @var: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: Always 0.
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
