#include "shell.h"

/**
 * read_input - function that reads throught the input
 *
 * Return: Buffer
 */
char *read_input(void)
{
	char *Buffer = NULL;
	size_t size = 0;
	ssize_t n;

	/* Non interactive mode */
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);

	n = _getline(&Buffer, &size, stdin);

	if (n == -1)
	{
		free(Buffer);
		Buffer = NULL;
		return (NULL);
	}

	return (Buffer);
}

/**
 * **get_token - function that tokenize string
 *
 * @input: string
 *
 * Return: Arrays of tokens
 */
char **get_token(char *input)
{
	const char *tok = NULL, *delim = " \t\n";
	char *cpy, **cmd;
	int i = 0, j = 0;

	if (!input)
		return (NULL);
	cpy = _strdup(input);

	tok = c_strtok(cpy, delim);
	if (tok == NULL)
	{
		free(input);
		free(cpy);
		cpy = NULL;
		return (NULL);
	}

	while (tok)
	{
		i++;
		tok = c_strtok(NULL, delim);
	}
	free(cpy);

	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
	{
		free(input), input = NULL;
		return (NULL);
	}
	tok = c_strtok(input, delim);
	while (tok)
	{
		cmd[j] = _strdup(tok);
		tok = c_strtok(NULL, delim);
		j++;
	}
	free(input), input = NULL;
	cmd[j] = NULL;
	return (cmd);
}

/**
 * run_execve - function that executes the input
 *
 * @cmd: tokenized commands
 * @program: Name of the program
 * @index: index of the command passed
 *
 * Return: status
 */

int run_execve(char **cmd, char *program, int index)
{
	char *all_cmd;
	pid_t child_pid;
	int status = 0;

	all_cmd = get_path(cmd[0]);
	if (!all_cmd)
	{
		print_error(program, cmd[0], index);
		Mem_free_check(cmd);
		return (127);
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(all_cmd, cmd, environ) == -1)
		{
			/* Executable not found */
			free(all_cmd), all_cmd = NULL;
			Mem_free_check(cmd);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		Mem_free_check(cmd);
		free(all_cmd), all_cmd = NULL;
	}

	return (WEXITSTATUS(status));
}

/**
 * getTokenLength - Number of tokens that can be retrieved
 * from an input
 *
 * @input: input
 * @delim: delimeter
 *
 * Return: count
 */
int getTokenLength(char *input, const char *delim)
{
	int count;
	char *currentToken;
	char *copied = strdup(input);

	count = 0;
	currentToken = strtok(copied, delim);

	if (currentToken == NULL)
	{
		free(input);
		free(copied);
	}

	count++;
	while (currentToken)
	{
		currentToken = strtok(NULL, delim);
		count++;
	}

	free(copied);
	return (count);
}
