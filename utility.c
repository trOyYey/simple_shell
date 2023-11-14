#include "shell.h"

/**
 * Mem_free_check - Free the allocated memory
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
 * printerror - function that prints error
 * @name: char pointer
 * @cmd: char pointer
 * @index: int
 * Return: void
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
 * @n: int
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
 * string_revere - reverse the string
 * @s: string
 * @l: lenght
 * Return: void
 */

void string_reverse(char *s, int l)
{
	int end = l -1;
	int start = 0;
	char temp;

	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}
