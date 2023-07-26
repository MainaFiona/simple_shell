#include "shell.h"

/**
 * is_chain - Checks if there is a command chaining
 * operator at a given buffer.
 * @info: Pointer to info_t struct.
 * @buff: input buffer.
 * @p: Pointer to the position in the buffer.
 *
 * Return: 1 if command operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - Checks the command chaining type and updates buffer position.
 * @info: Pointer to info_t struct.
 * @buff: input buffer.
 * @p: Pointer to position in buffer.
 * @i: Current index in buffer.
 * @len: Length of buffer.
 *
 * Return: Always 0
 */
void check_chain(info_t *info, char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Changes command with an alias if found.
 * @info: Pointer to info_t struct.
 *
 * Return: 1 if an alias is replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _custom_strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
/**
 * replace_vars - Replaces variables in the command arguments.
 * @info: Pointer to the info_t struct.
 *
 * Return: Always 0.
 */

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_num_base(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_num_base(getpid(), 10, 0)));
			continue;
		}
		node = node_start_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_custom_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}
/**
 * replace_string - Replaces old string with new string.
 * @old: Pointer to  old string.
 * @new: Pointer to new string.
 *
 * Return: 1 on success, or -1 on failure.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
