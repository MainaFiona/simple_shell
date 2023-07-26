#include "main.h"

/**
 * _eputs - Writes a string to standard error.
 * @str: The string to be written.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - Writes a character to standard error.
 * @c: The character to be written.
 *
 * Return: 1 on success, or -1 on failure.
 */
int _eputchar(char c)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}
/**
 * _putfd - Writes a character to a file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: 1 on success, or -1 on failure.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * _putsfd - Writes a string to a file descriptor.
 * @str: The string to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
