#include "my_shell.h"

/**
 * my_env - Print the current environment.
 * @info: Structure containing potential arguments.
 *
 * Returns: Always 0.
 */
int my_env(MyShellInfo *info)
{
    print_my_list_string(info->environment);
    return 0;
}

/**
 * _getenv - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Returns: The value.
 */
char *_getenv(MyShellInfo *info, const char *name)
{
    MyList *node = info->environment;
    char *p;

    while (node)
    {
        p = my_starts_with(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * my_set_env - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 *
 * Returns: Always 0.
 */
int my_set_env(MyShellInfo *info)
{
    if (info->argumentCount != 3)
    {
        my_puts("Incorrect number of arguments\n");
        return 1;
    }
    if (my_setenv(info, info->arguments[1], info->arguments[2]))
        return 0;
    return 1;
}

/**
 * my_unset_env - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Returns: Always 0.
 */
int my_unset_env(MyShellInfo *info)
{
    int i;

    if (info->argumentCount == 1)
    {
        my_puts("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i < info->argumentCount; i++)
        my_unsetenv(info, info->arguments[i]);

    return 0;
}

/**
 * populate_my_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Returns: Always 0.
 */
int populate_my_env_list(MyShellInfo *info)
{
    MyList *node = NULL;
    size_t i;

    for (i = 0; info->my_environ[i]; i++)
        add_my_node_end(&node, info->my_environ[i], 0);
    info->environment = node;
    return 0;
}
