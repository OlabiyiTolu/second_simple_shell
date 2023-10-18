#include "shell.h"

/**
 * list_length - determines the length of a linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t list_length(const MyList *head)
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
 * MyListo_strings - returns an array of strings from the list
 * @head: Pointer to the first node
 *
 * Return: Array of strings
 */
char **list_to_strings(list_t *head)
{
    MyList *node = head;
    size_t list_size = list_length(head);
    char **strings;
    size_t i, j;

    if (!head || !list_size)
        return NULL;

    strings = malloc(sizeof(char *) * (list_size + 1));
    if (!strings)
        return NULL;

    for (i = 0; node; node = node->next, i++)
    {
        char *str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        _strcpy(str, node->str);
        strings[i] = str;
    }

    strings[i] = NULL;
    return strings;
}

/**
 * print_list - prints all elements of a MyList linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list(const MyList *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _puts(": ");
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * find_node_starts_with - returns a node whose string starts with a prefix
 * @node: Pointer to the list head
 * @prefix: String to match
 * @c: The next character after the prefix to match
 *
 * Return: Matching node or NULL
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * get_node_index - gets the index of a node in a list
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: Index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, MyList *node)
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