#include "main.h"
/**
 * _strlen - will return the len of a str
 *
 * @s: str which len will be returned
 * Return: len of str
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}
/**
 * _strcmp - will compare ywo str
 * @s1: str to compare
 * @s2: char to compare to str
 * Return: -1 if s1 less than s2, 1 if s1 greater that s2, 0 if equal
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - will verify if needle starts with haystack
 * @haystack: the str to be searched
 * @needle: substr to be located
 * Return: location of the following char
 *
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - it will concate two str
 * @dest: buffer dest
 * @src: buffer src
 * Return: dest to pointer buff
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
