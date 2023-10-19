#include "shell.h"

/**
 * is_my_command - Checks if a file is an executable command.
 * @info: The MyShellInfo struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_my_command(MyShellInfo *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st) != 0) {
        return 0;
    }

    if (st.st_mode & S_IFREG) {
        return 1;
    }
    return 0;
}

/**
 * duplicate_characters - Duplicates characters within a range.
 * @pathstr: The input string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *duplicate_characters(char *pathstr, int start, int stop)
{
    char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++) {
        if (pathstr[i] != ':') {
            buf[k++] = pathstr[i];
        }
    }
    buf[k] = 0;
    return strdup(buf);
}

/**
 * find_my_path - Finds the command path in the PATH string.
 * @info: The MyShellInfo struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_my_path(MyShellInfo *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr) {
        return NULL;
    }

    if (strlen(cmd) > 2 && my_starts_with(cmd, "./")) {
        if (is_my_command(info, cmd)) {
            return cmd;
        }
    }

    while (1) {
        if (!pathstr[i] || pathstr[i] == ':') {
            path = duplicate_characters(pathstr, curr_pos, i);
            if (!*path) {
                strcat(path, cmd);
            } else {
                strcat(path, "/");
                strcat(path, cmd);
            }
            if (is_my_command(info, path)) {
                return path;
            }
            if (!pathstr[i]) {
                break;
            }
            curr_pos = i;
        }
        i++;
    }

    return NULL;
}
