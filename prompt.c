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
	char *Buffer = NULL;
	size_t size = 0;
	ssize_t n;
	
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);
	n = getline(&Buffer, &size, stdin);
	if ( n == -1)
	{
		free(Buffer);
		return (NULL);
	}
	return (Buffer);
}

/**
 * **get_token - function that tokenize string
 * @input_line: string
 * Return:
 */

char **get_token(char *input_line)
{
	char *tok = NULL,*cpy = NULL, delim[] = " \t\n";
	char **cmd = NULL;
	int i = 0, j = 0;

	if (!input_line)
		return (NULL);

	cpy = _strdup(input_line);

	tok = strtok(cpy, delim);
	if (tok == NULL)
	{
		free(input_line), input_line = NULL;
		free(cpy), cpy = NULL;
		return (NULL);
	}

	while (tok)
	{
		i++;
		tok = strtok(NULL, delim);
	}
	free(cpy), cpy = NULL;

	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
	{
		free(input_line), input_line = NULL;
		return (NULL);
	}

	tok = strtok(input_line, delim);
	while (tok)
	{
		cmd[j] = _strdup(tok);
		tok = strtok(NULL, delim);
		j++;
	}
	free(input_line), input_line = NULL;
	cmd[j] = NULL;
	return (cmd);
}
