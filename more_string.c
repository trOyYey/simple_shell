#include "shell.h"

/*
 * _strncmp - compares input with counted chars only
 * @dest: input
 * @source: the selected string
 * @counter: number of char to compare
 * Return: 0 if succeded
 */

int _strncmp(const char *dest, char *source, int counter)
{
	while (counter && *dest == *source)
	{
		counter--;
		dest++;
		source++;
	}
	if (counter)
		return (*dest - *source);

	return (0);
}
