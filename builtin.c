#include "shell.h"

/**
 * my_exit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info->arguments[0] != "exit."
 */
 
int my_exit(MyShellInfo *info)
{
	int exitcheck;

	if (info->arguments[1])  /* If there is an exit argument */
	{
		exitcheck = my_error_atoi(info->arguments[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_my_error(info, "Illegal number: ");
			my_puts(info->arguments[1]);
			my_putchar('\n');
			return 1;
		}
		info->errorNumber = my_error_atoi(info->arguments[1]);
		return -2;
	}
	info->errorNumber = -1;
	return -2;
}

/**
 * my_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * Return: Always 0.
 */

int my_cd(MyShellInfo *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arguments[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(info->arguments[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			my_puts(s);
			my_putchar('\n');
			return 1;
		}
		my_puts(_getenv(info, "OLDPWD="));
		my_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->arguments[1]);
	if (chdir_ret == -1)
	{
		print_my_error(info, "can't cd to ");
		my_puts(info->arguments[1]);
		my_putchar('\n');
	}
	else
	{
		my_set_env(info, "OLDPWD", _getenv(info, "PWD="));
		my_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * my_help - Provides help for the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * Return: Always 0.
 */

int my_help(MyShellInfo *info)
{
	char **arg_array;

	arg_array = info->arguments;
	my_puts("help call works. Function not yet implemented\n");
	if (0)
		my_puts(*arg_array); /* temp att_unused workaround */
	return 0;
}
