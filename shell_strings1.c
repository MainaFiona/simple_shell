#include "main.h"
/**
 * _strcpy - function that copies a string
 * @dest: destination strin
 *
 * @src: source string
 *
 * Return: pointer to the destinatin
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _strdup - fuction that duplicates a string
 *
 * @str: string to be duplicaated
 *
 * Return: pointer to the dulpicate
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 * _puts - function that prints input
 *
 * @str: string to print
 *
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
/**
 * _putchar - function to write char to stdout
 *
 * @c: char to be printed
 *
 * Return: Success 1, else -1
 */
int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

