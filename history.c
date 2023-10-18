#include "shell.h"

/**
 * add_node_my_end - adds a node to the end of a linked list
 * @head: pointer to the head of the linked list
 * @str: string to add to the node
 * @lineCount: line count
 *
 * Return: pointer to the new node
 */
MyList *add_node_my_end(MyList **head, char *str, int lineCount) {
  MyList *node = malloc(sizeof(MyList));
  if (!node) {
    return NULL;
  }

  node->str = malloc(sizeof(char) * (strlen(str) + 1));
  if (!node->str) {
    free(node);
    return NULL;
  }

  strcpy(node->str, str);
  node->num = lineCount;
  node->next = NULL;

  if (*head == NULL) {
    *head = node;
  } else {
    MyList *temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = node;
  }

  return node;
}

/**
 * write_my_history - writes history to a file
 * @info: Structure containing potential arguments.
 *
 * Return: 1 on success, else -1
 */
int write_my_history(MyShellInfo *info) {
  FILE *file;
  MyList *node;

  char *filename = get_my_history_file(info);
  if (!filename) {
    return -1;
  }

  file = fopen(filename, "w");
  if (!file) {
    free(filename);
    return -1;
  }

  node = info->history;
  while (node) {
    fprintf(file, "%s\n", node->str);
    node = node->next;
  }

  fclose(file);
  free(filename);
  return 1;
}

/**
 * read_my_history - reads history from a file
 * @info: Structure containing potential arguments.
 *
 * Return: histcount on success, 0 otherwise
 */
int read_my_history(MyShellInfo *info) {
  FILE *file;
  char line[MY_HIST_MAX];
  int linecount = 0;

  char *filename = get_my_history_file(info);
  if (!filename) {
    return 0;
  }

  file = fopen(filename, "r");
  if (!file) {
    free(filename);
    return 0;
  }

  while (fgets(line, MY_HIST_MAX, file)) {
    line[strlen(line) - 1] = '\0'; /* Remove newline */
    build_my_history_list(info, line, linecount);
    linecount++;
  }

  fclose(file);
  free(filename);
  return linecount;
}
