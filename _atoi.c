#include "my_shell.h"

/**
 * my_interact - Check if the shell is in interactive mode.
 * @info: Pointer to the struct holding information.
 *
 * Returns: 1 if in interactive mode, 0 otherwise.
 */
int my_interact(MyShellInfo *info)
{
    return (isatty(STDIN_FILENO) && info->readFd <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Returns: 1 if it's a delimiter, 0 if not.
 */
int is_delimiter(char c, char *delim)
{
    while (*delim) {
        if (*delim == c) {
            return 1;
        }
        delim++;
    }
    return 0;
}

/**
 * my_is_alpha - Check if a character is alphabetic.
 * @c: The character to check.
 *
 * Returns: 1 if it's alphabetic, 0 if not.
 */
int my_is_alpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

/**
 * my_atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Returns: 0 if no numbers in the string, the converted number otherwise.
 */
int my_atoi(char *s)
{
    int i, sign = 1, flag = 0, output = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++) {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            output *= 10;
            output += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    return (sign == -1) ? -output : output;
}