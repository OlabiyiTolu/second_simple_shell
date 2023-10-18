#include "shell.h"

/**
 * add_my_node - adds a node to the start of the list
 * @head: Address of the pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Address of the newly added node
 */
MyList *add_my_node(MyList **head, const char *str, int num)
{
    MyList *new_node;

    if (!head)
        return NULL;
    new_node = malloc(sizeof(MyList));
    if (!new_node)
        return NULL;
    _memset((void *)new_node, 0, sizeof(MyList));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }
    new_node->next = *head;
    *head = new_node;
    return new_node;
}

/**
 * add_my_node_end - adds a node to the end of the list
 * @head: Address of the pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Address of the newly added node
 */
MyList *add_my_node_end(MyList **head, const char *str, int num)
{
    MyList *new_node, *node;

    if (!head)
        return NULL;

    node = *head;
    new_node = malloc(sizeof(MyList));
    if (!new_node)
        return NULL;
    _memset((void *)new_node, 0, sizeof(MyList));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
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
    return new_node;
}

/**
 * print_my_list_string - prints only the str element of a MyList linked list
 * @head: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */
size_t print_my_list_string(const MyList *head)
{
    size_t i = 0;

    while (head)
    {
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        i++;
    }
    return i;
}

/**
 * delete_my_node_at_index - deletes a node at the given index
 * @head: Address of the pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_my_node_at_index(MyList **head, unsigned int index)
{
    MyList *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }
    node = *head;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return 0;
}

/**
 * free_my_list - frees all nodes of a list
 * @head_ptr: Address of the pointer to the head node
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