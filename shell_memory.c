#include "main.h"
/**
 * bfree - will free pointer and null adress
 *
 * @ptr: pointer address to be freed
 * Return: 1 if free, else 0
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
