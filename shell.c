#include "shell.h"

/**
 * read_input - function that reads throught the input
 *
 * @status: updates when enter key is entered
 *
 * Return: Buffer
 */
char *read_input(int *status)
{
	char *Buffer = NULL;
	size_t size = 0;
	ssize_t n;

	/* Non interactive mode */
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);

	n = getline(&Buffer, &size, stdin);

	if (n == -1)
	{
		free(Buffer);
		return (NULL);
	}
	else if (n == 1)
		*status = 1;

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
	char *tok, **cmd;
	const char *delim = " \t\n";
	int size, i;

	if (!input)
		return (NULL);

	/* number of tokens */
	size = getTokenLength(input, delim);

	cmd = malloc(sizeof(char *) * (size + 1));

	/* failed allocation of memory */
	if (!cmd)
	{
		free(input);
		input = NULL;
		return (NULL);
	}

	/* Store tokens in the vector */
	tok = strtok(input, delim);
	i = 0;
	while (tok)
	{
		cmd[i] = _strdup(tok);
		tok = strtok(NULL, delim);
		i++;
	}

	free(input);

	cmd[i] = NULL;

	return (cmd);
}

/**
 * run_execve - function that executes the input
 *
 * @cmd: tokenized commands
 * @program: Name of the program
 *
 * Return: status
 */

int run_execve(char **cmd, char **program)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(cmd[0], cmd, environ) == -1)
		{
			/* Executable not found */
			perror(*program);
			Mem_free_check(cmd);
			exit(0);
		}
	}
	else if (child_pid > 0)
	{
		waitpid(child_pid, &status, 0);
		Mem_free_check(cmd);
	}
	else
	{
		dprintf(STDERR_FILENO, "forked failed\n");
		exit(EXIT_FAILURE);
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
