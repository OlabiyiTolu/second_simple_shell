#include "shell.h"

/**
 * my_input_buffer - buffers chained commands
 * @info: MyShellInfo struct
 * @buffer: address of the buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t my_input_buffer(MyShellInfo *info, char **buffer, size_t *length)
{
    ssize_t read_bytes = 0;
    size_t length_p = 0;

    if (!*length) /* if nothing left in the buffer, fill it */
    {
        /* my_bfree((void **)info->commandBuffer); */
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, my_sigint_handler);
#if MY_USE_GETLINE
        read_bytes = my_getline(buffer, &length_p, stdin);
#else
        read_bytes = my_get_line(info, buffer, &length_p);
#endif
        if (read_bytes > 0)
        {
            if ((*buffer)[read_bytes - 1] == '\n')
            {
                (*buffer)[read_bytes - 1] = '\0'; /* remove trailing newline */
                read_bytes--;
            }
            info->lineCountFlag = 1;
            remove_comments(*buffer);
            build_my_history_list(info, *buffer, info->historyCount++);
            /* if (my_strchr(*buffer, ';')) is this a command chain? */
            {
                *length = read_bytes;
                info->commandBuffer = buffer;
            }
        }
    }
    return read_bytes;
}

/**
 * my_get_input - gets a line minus the newline
 * @info: MyShellInfo struct
 *
 * Return: bytes read
 */
ssize_t my_get_input(MyShellInfo *info)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t i, j, length;
    ssize_t read_bytes = 0;
    char **buffer_p = &(info->argument), *p;

    my_putchar(MY_BUF_FLUSH);
    read_bytes = my_input_buffer(info, &buffer, &length);
    if (read_bytes == -1) /* EOF */
        return -1;
    if (length) /* we have commands left in the chain buffer */
    {
        j = i;       /* init new iterator to current buffer position */
        p = buffer + i; /* get pointer for return */

        check_my_chain(info, buffer, &j, i, length);
        while (j < length) /* iterate to semicolon or end */
        {
            if (is_my_chain(info, buffer, &j))
                break;
            j++;
        }

        i = j + 1;     /* increment past nulled ';'' */
        if (i >= length) /* reached end of buffer? */
        {
            i = length = 0; /* reset position and length */
            info->commandBufferType = MY_CMD_NORM;
        }

        *buffer_p = p; /* pass back pointer to current command position */
        return my_strlen(p); /* return length of current command */
    }

    *buffer_p = buffer; /* else not a chain, pass back buffer from my_getline() */
    return read_bytes;   /* return length of buffer from my_getline() */
}

/**
 * my_read_buffer - reads a buffer
 * @info: MyShellInfo struct
 * @buffer: buffer
 * @i: size
 *
 * Return: read_bytes
 */
ssize_t my_read_buffer(MyShellInfo *info, char *buffer, size_t *i)
{
    ssize_t read_bytes = 0;

    if (*i)
        return 0;
    read_bytes = read(info->readFd, buffer, MY_READ_BUF_SIZE);
    if (read_bytes >= 0)
        *i = (size_t)read_bytes;
    return read_bytes;
}

/**
 * my_get_line - gets the next line of input from STDIN
 * @info: MyShellInfo struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int my_get_line(MyShellInfo *info, char **ptr, size_t *length)
{
    static char buffer[MY_READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t read_bytes = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        k = *length;
    if (i == len)
        i = len = 0;

    read_bytes = my_read_buffer(info, buffer, &len);
    if (read_bytes == -1 || (read_bytes == 0 && len == 0))
        return -1;

    c = my_strchr(buffer + i, '\n');
    k = c ? 1 + (size_t)(c - buffer) : len;
    new_p = my_realloc(p, k, p ? k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return p ? (free((void **)p), -1) : -1;

    if (p)
        my_strncat(new_p, buffer + i, k - i);
    else
        my_strncpy(new_p, buffer + i, k - i + 1);

    k -= i;
    i = k;
    p = new_p;

    if (length)
        *length = k;
    *ptr = p;
    return k;
}

/**
 * my_sigint_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void my_sigint_handler(__attribute__((unused)) int sig_num)
{
    my_puts("\n");
    my_puts("$ ");
    my_putchar(MY_BUF_FLUSH);
}
