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

/**
 * print_error - Function that prints error
 *
 * @name: Command name
 * @cmd:  Tokenized commands
 * @index: index of the command entered
 *
 * Return: void (Nothing);
 */
void print_error(char *name, char *cmd, int index)
{
	char *idx, massege[] = ": not found\n";

	idx = _itoa(index);

	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, idx, _strlen(idx));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, massege, _strlen(massege));

	free(idx);
}

/**
 * _itoa - function that changes int to char
 * @N: int
 * Return: char
 */
char *_itoa(int N)
{
	char Buffer[15];
	int i = 0;

	if (N == 0)
		Buffer[i++] = '0';
	else
	{
		while (N > 0)
		{
			Buffer[i++] = (N % 10) + '0';
			N /= 10;
		}
	}

	Buffer[i] = '\0';
	string_reverse(Buffer, i);
	return (_strdup(Buffer));
}

/**
 * string_reverse - reverse the string
 *
 * @s: string
 * @l: lenght
 *
 * Return: void
 */
void string_reverse(char *s, int l)
{
	int end, start;

	end = l - 1;
	start = 0;

	while (start < end)
	{
		char temp = s[start];

		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}
