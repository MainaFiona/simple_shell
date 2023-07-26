#include "main.h"

/**
 * interactive - true if shell is interactive
 * @info: structure address
 *
 * Return: 1 if true else 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - looks if character is delimeter
 * @c: char to be checked
 * @delimit: delimeter string
 *
 * Return: 1 for true, 0 for false
 */
int is_delim(char c, char *delimit)
{
	while (*delimit)
		if (*delimit++ == c)
			return (1);
	return (0);
}
/**
 * isalpha - looks for alphabets
 * @c: char to input
 *
 * Return: 1 if alphabets 0 if false
 */
int isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - funcion converts string to int
 * @s: string to convert
 *
 * Return: Always 0
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
