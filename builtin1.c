#include "my_shell.h"

/**
 * my_history - Display the command history with line numbers.
 * @info: Pointer to the struct containing potential arguments.
 * Return: Always 0.
 */
int my_history(MyShellInfo *info)
{
    print_my_list_string(info->history);
    return 0;
}

/**
 * unset_my_alias - Unset an alias.
 * @info: Pointer to the struct containing potential arguments.
 * @str: The alias string to unset.
 * Return: 0 on success, 1 on error.
 */
int unset_my_alias(MyShellInfo *info, char *str)
{
    char *p, c;
    int ret;

    p = my_strchr(str, '=');
    if (!p)
        return 1;
    c = *p;
    *p = 0;
    ret = delete_my_node_at_index(&(info->alias), get_my_node_index(info->alias, my_node_starts_with(info->alias, str, '=')));
    *p = c;
    return ret;
}

/**
 * set_my_alias - Set an alias to a string.
 * @info: Pointer to the struct containing potential arguments.
 * @str: The alias string to set.
 * Return: 0 on success, 1 on error.
 */
int set_my_alias(MyShellInfo *info, char *str)
{
    char *p;

    p = my_strchr(str, '=');
    if (!p)
        return 1;
    if (!*++p)
        return unset_my_alias(info, str);

    unset_my_alias(info, str);
    return (add_my_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_my_alias - Print an alias string.
 * @node: The alias node.
 * Return: 0 on success, 1 on error.
 */
int print_my_alias(MyList *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = my_strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            my_putchar(*a);
        my_putchar('\'');
        my_puts(p + 1);
        my_puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * my_alias - Mimic the alias built-in (man alias).
 * @info: Pointer to the struct containing potential arguments.
 * Return: Always 0.
 */
int my_alias(MyShellInfo *info)
{
    int i = 0;
    char *p = NULL;
    MyList *node = NULL;

    if (info->argumentCount == 1)
    {
        node = info->alias;
        while (node)
        {
            print_my_alias(node);
            node = node->next;
        }
        return 0;
    }
    for (i = 1; info->arguments[i]; i++)
    {
        p = my_strchr(info->arguments[i], '=');
        if (p)
            set_my_alias(info, info->arguments[i]);
        else
            print_my_alias(my_node_starts_with(info->alias, info->arguments[i], '='));
    }

    return 0;
}
