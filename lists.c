#include "shell.h"

/**
 * add_my_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
 
MyList *add_my_node(MyList **head, const char *str, int num)
{
    MyList *new_head;

    if (!head)
        return (NULL);

    new_head = malloc(sizeof(MyList));
    if (!new_head)
        return (NULL);

    my_memset((void *)new_head, 0, sizeof(MyList));
    new_head->number = num;

    if (str)
    {
        new_head->str = my_strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }

    new_head->next = *head;
    *head = new_head;

    return (new_head);
}

/**
 * add_my_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

MyList *add_my_node_end(MyList **head, const char *str, int num)
{
    MyList *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(MyList));
    if (!new_node)
        return (NULL);

    my_memset((void *)new_node, 0, sizeof(MyList));
    new_node->number = num;

    if (str)
    {
        new_node->str = my_strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;

    return (new_node);
}

/**
 * print_my_list_string - prints only the str element of a MyList linked list
 * @h: pointer to the first node
 *
 * Return: size of list
 */

size_t print_my_list_string(const MyList *h)
{
    size_t i = 0;

    while (h)
    {
        my_puts(h->str ? h->str : "(nil)");
        my_puts("\n");
        h = h->next;
        i++;
    }

    return (i);
}

/**
 * delete_my_node_at_index - deletes a node at a given index
 * @head: address of pointer to the first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_my_node_at_index(MyList **head, unsigned int index)
{
    MyList *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }

    node = *head;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prev_node = node;
        node = node->next;
    }

    return (0);
}

/**
 * free_my_list - frees all nodes of a list
 * @head_ptr: address of pointer to the head node
 *
 * Return: void
 */

void free_my_list(MyList **head_ptr)
{
    MyList *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;

    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}
