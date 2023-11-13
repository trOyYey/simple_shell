#include "shell.h"

/**
 * main - simple shell
 * @ac: counter
 * @av: argument
 * Return: 0
 */

int main(int ac, char **argv)
{
	char *input_line = NULL;
	char **input_command = NULL;
	int stat = 0;

	while (1)
	{
		input_line = analyze_line();
		if (input_line == NULL)  /* EOF */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (stat);
		}
		free(input_line);
