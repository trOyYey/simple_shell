#include "shell.h"

/**
 * analyze_line - function that reads throught the input
 * @Buffer: buffer
 * @N: ssize_t
 * @size: size of buffer
 * Return: Buffer
 */

char *analyze_line(void)
{
	char *Buffer = Null;
	size_t size = 0;
	ssize_t n;
	
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9)
	n = getline(&Buffer, &size, stdin);
	if ( n == -1)
	{
		free(Buffer);
		return (NULL);
	}
	return (Buffer);
}
