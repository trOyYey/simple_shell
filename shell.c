#include "shell.h"

/**
 * analyze_line - function that reads throught the input
 * @Buffer: buffer
 * @N: ssize_t
 * @size: size of buffer
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

	n = getline(&Buffer, &size, stdin);

	if ( n == -1)
	{
		free(Buffer), Buffer = NULL;
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

/**
 * run_execve - function that executes the input
 * @cmd:
 * @argv:
 * Return: int
 */

int run_execve(char **cmd, char **argv, int index)
{
	char *all_cmd;
	pid_t child_pid;
	int status = 0;

	all_cmd = get_path(cmd[0]);
	if(!all_cmd)
	{
		print_error(argv[0], cmd[0], index);
		Mem_free_check(cmd);
		return(127);
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
	return(WEXITSTATUS(status));
}

