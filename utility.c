#include "shell.h"

/**
 * Mem_free_check - Free the allocated memory
 *
 * @cmd: The tokenized commands
 *
 * Return: Void
 */
void Mem_free_check(char **cmd)
{
	int i;

	if (!cmd)
		return;
	for (i = 0; cmd[i]; i++)
	{
		free(cmd[i]);
			cmd[i] = NULL;
	}
	free(cmd), cmd = NULL;
}

/**
 * _atoi - convert string into numbers
 *
 * @s: string to be coverted
 *
 * Return: the number
 */
int _atoi(char *s)
{
	int i, isNegative, number, length, isNumber, digit;

	isNegative = 0, number = 0, length = 0;
	isNumber = false;

	/* Get length of the string */
	while (*(s + length))
		length++;

	i = 0;
	/* Convert the string to number */
	while (i < length && !isNumber)
	{
		if (s[i] == '-')
			++isNegative;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';

			/* Handles negative number */
			if (isNegative % 2)
				digit = -digit;

			number = number * 10 + digit;
			isNumber = true;

			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;

			isNumber = false;
		}
		i++;
	}
	if (!isNumber)
		return (0);

	return (number);
}
