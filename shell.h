#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Define buffer sizes for reading and writing. */
#define MY_READ_BUF_SIZE 1024
#define MY_WRITE_BUF_SIZE 1024
#define MY_BUF_FLUSH -1

/* Define constants for command chaining. */
#define MY_CMD_NORM 0
#define MY_CMD_OR 1
#define MY_CMD_AND 2
#define MY_CMD_CHAIN 3

/* Define constants for converting numbers. */
#define MY_CONVERT_LOWERCASE 1
#define MY_CONVERT_UNSIGNED 2

/* Define flags for using getline and strtok. */
#define MY_USE_GETLINE 0
#define MY_USE_STRTOK 0

/* Define the history file and maximum history size. */
#define MY_HIST_FILE ".my_shell_history"
#define MY_HIST_MAX 4096

extern char **my_environ;

/**
 * struct MyListString - singly linked list
 * @number: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct MyListString {
    int number;
    char *str;
    struct MyListString *next;
} MyList;

/**
 *struct MyShellInfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argument: a string generated from getline containing arguements
 *@arguments: an array of strings generated from arg
 *@path: a string path for the current command
 *@argumentCount: the argument count
 *@lineCount: the error count
 *@errorNumber: the error code for exit()s
 *@lineCountFlag: if on count this line of input
 *@fileName: the program filename
 *@environment: linked list local copy of environ
 *@my_environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@environmentChanged: on if environ was changed
 *@status: the return status of the last exec'd command
 *@commandBuffer: address of pointer to cmd_buf, on if chaining
 *@commandBufferType: CMD_type ||, &&, ;
 *@readFd: the fd from which to read line input
 *@historyCount: the history line number count
 */
typedef struct MyShellInfo
{
    char *argument;
    char **arguments;
    char *path;
    int argumentCount;
    unsigned int lineCount;
    int errorNumber;
    int lineCountFlag;
    char *fileName;
    MyList *environment;
    MyList *history;
    MyList *alias;
    char **my_environ;
    int environmentChanged;
    int status;
    char **commandBuffer;
    int commandBufferType;
    int readFd;
    int historyCount;
} MyShellInfo;

/* Initialize a MyShellInfo structure with default values. */
#define MY_SHELL_INFO_INIT                                                      \
    {                                                                           \
        NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
            0, 0, 0, 0, 0, NULL, 0                                                 \
    }

/**
 *struct MyBuiltIn - contains a MyBuiltIn string and related function
 *@type: the MyBuiltIn command flag
 *@function: the function
 */
typedef struct MyBuiltIn {
    char *type;
    int (*function)(MyShellInfo *);
} MyBuiltInTable;

/* Function prototypes for shell.c and related functions. */
int my_shell(MyShellInfo *, char **);
int find_my_built_in(MyShellInfo *);
void find_my_command(MyShellInfo *);
void fork_my_command(MyShellInfo *);

/* Function prototypes for parser.c and related functions. */
int is_my_command(MyShellInfo *, char *);
char *duplicate_characters(char *, int, int);
char *find_my_path(MyShellInfo *, char *, char *);

/* Function prototypes for loophsh.c and related functions. */
int loop_my_shell(char **);

/* Function prototypes for errors.c and related functions. */
void my_puts(char *);
int my_putchar(char);
int put_fd(char, int fd);
int puts_fd(char *str, int fd);

/* Function prototypes for string.c and related functions. */
int my_strlen(char *);
int my_strcmp(char *, char *);
char *my_starts_with(const char *, const char *);
char *my_strcat(char *, char *);

/* Function prototypes for string1.c and related functions. */
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

/* Function prototypes for exits.c and related functions. */
char *my_strncpy(char *dst, const char *src, int n);
char *my_strncat(char *dst, const char *src, int n);
char *my_strchr(const char *s, int c);

/* Function prototypes for tokenizer.c and related functions. */
char **my_strtow(char *, char *);
char **my_strtow2(char *, char);

/* Function prototypes for realloc.c and related functions. */
char *my_memset(char *, char, unsigned int);
void my_ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* Function prototypes for memory.c and related functions. */
int my_bfree(void **);

/* Function prototypes for atoi.c and related functions. */
int my_interact(MyShellInfo *);
int is_delimiter(char, char *);
int my_is_alpha(int);
int my_atoi(char *);

/* Function prototypes for errors1.c and related functions. */
int my_error_atoi(char *);
void print_my_error(MyShellInfo *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Function prototypes for builtin.c and related functions. */
int my_exit(MyShellInfo *);
int my_cd(MyShellInfo *);
int my_help(MyShellInfo *);

/* Function prototypes for builtin1.c and related functions. */
int my_history(MyShellInfo *);
int my_alias(MyShellInfo *);

/* Function prototypes for getline.c and related functions. */
ssize_t my_get_input(MyShellInfo *);
int my_get_line(MyShellInfo *, char **, size_t *);
void sigint_handler(int);

/* Function prototypes for getinfo.c and related functions. */
void clear_my_info(MyShellInfo *);
void set_my_info(MyShellInfo *, char **);
void free_my_info(MyShellInfo *, int);

/* Function prototypes for environ.c and related functions. */
char *_getenv(MyShellInfo *, const char *);
int my_env(MyShellInfo *);
int my_mset_env(MyShellInfo *);
int my_munset_env(MyShellInfo *);
int populate_my_env_list(MyShellInfo *);

/* Function prototypes for getenv.c and related functions. */
char **get_my_environ(MyShellInfo *);
int my_unset_env(MyShellInfo *, char *);
int my_set_env(MyShellInfo *, char *, char *);

/* Function prototypes for history.c and related functions. */
char *get_my_history_file(MyShellInfo *info);
int write_my_history(MyShellInfo *info);
int read_my_history(MyShellInfo *info);
int build_my_history_list(MyShellInfo *info, char *buf, int lineCount);
int renumber_my_history(MyShellInfo *info);

/* Function prototypes for lists.c and related functions. */
MyList *add_my_node(MyList **, const char *, int);
MyList *add_my_node_end(MyList **, const char *, int);
size_t print_my_list_string(const MyList *);
int delete_my_node_at_index(MyList **, unsigned int);
void free_my_list(MyList **);

/* Function prototypes for lists1.c and related functions. */
size_t my_list_len(const MyList *);
char **my_list_to_strings(MyList *);
size_t print_my_list(const MyList *);
MyList *my_node_starts_with(MyList *, char *, char);
ssize_t get_my_node_index(MyList *, MyList *);

/* Function prototypes for vars.c and related functions. */
int is_my_chain(MyShellInfo *, char *, size_t *);
void check_my_chain(MyShellInfo *, char *, size_t *, size_t, size_t);
int replace_my_alias(MyShellInfo *);
int replace_my_vars(MyShellInfo *);
int replace_my_string(char **, char *);

#endif