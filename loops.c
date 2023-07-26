#include "main.h"
/**
 * hsh - Main shell loop that reads input,
 * executes commands, and handles builtins.
 * @info: Pointer to the info_t structure.
 * @av: Array of command-line arguments.
 *
 * Return: return value of the last executed builtn
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_etr = 0;

	for (; r != -1 && builtin_etr != -2;)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUFF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_etr = find_builtin(info);
			if (builtin_etr == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_etr == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_etr);
}

/**
 * find_builtin - Search for a builtin command and
 * execute it if found.
 * @info: Pointer to the info_t structure.
 *
 * Return: The return value of the executed
 * builtin command or -1 if not found.
 */
int find_builtin(info_t *info)
{
	int i, builtin_etr = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type != NULL; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_etr = builtintbl[i].func(info);
			break;
		}
	}

	return (builtin_etr);
}
/**
 * find_cmd - Find and execute a command.
 * @info: Pointer to the info_t structure.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	}

	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Fork a child process and execute the command.
 * @info: Pointer to the info_t structure.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
