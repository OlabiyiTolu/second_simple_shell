#include "shell.h"

/**
 * my_list_len - Determine the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */

size_t my_list_len(const MyList *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

/**
 * my_list_to_strings - Return an array of strings from the list.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */

char **my_list_to_strings(MyList *head)
{
    MyList *node = head;
    size_t list_size = my_list_len(head);
    char **strings;
    size_t i, j;

    if (!head || !list_size)
        return NULL;

    strings = malloc(sizeof(char *) * (list_size + 1));
    if (!strings)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        char *str = malloc(my_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        my_strcpy(str, node->str);
        strings[i] = str;
    }

    strings[i] = NULL;
    return strings;
}

/**
 * print_my_list - Print all elements of a MyList linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */

size_t print_my_list(const MyList *head)
{
    size_t count = 0;

    while (head)
    {
        my_puts(convert_number(head->number, 10, 0));
        my_puts(": ");
        my_puts(head->str ? head->str : "(nil)");
        my_puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * my_node_starts_with - Return a node whose string starts with a prefix.
 * @head: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL.
 */

MyList *my_node_starts_with(MyList *head, char *prefix, char c)
{
    char *p = NULL;

    while (head)
    {
        p = my_starts_with(head->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return head;
        head = head->next;
    }
    return NULL;
}

/**
 * get_my_node_index - Get the index of a node in a list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of the node or -1 if not found.
 */
 
ssize_t get_my_node_index(MyList *head, MyList *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}
