#include "shell.h"


/**
 * exit_command - exit builtin command
 *
 * @cmd: tokenized commands
 *
 * Return: exit status if the function fails
 * otherwise exit
 */
int exit_command(char *cmd[])
{
	int argCount, i, status;
	const int length = 6;

	argCount = 0;
	i = 0;

	/* Check for too many arguments */
	while (cmd[i++])
	{
		argCount++;
		if (argCount > 2)
			return (2); /* failed */
	}

	/* Contains exit status */
	if (cmd[1] != NULL)
	{
		status = _atoi(cmd[1]);
		Mem_free_check(cmd);
		write(1, "exit\n", length);
		exit(status);
	}

	/* does not contain status */
	write(1, "exit\n", length);
	Mem_free_check(cmd);
	exit(EXIT_SUCCESS);
}

/**
 * run_builtin - Checks if a command is builtin
 * and executes
 *
 * @cmd: The tokenized commands
 *
 * Return: executes the builtin, 0 if commands
 * entered does not match any builtin specified
 */
int run_builtin(char **cmd)
{
	int i, status;

	/* map command name to it function */
	Command builtin_command[] = {
		{"exit", exit_command},
		{"env", env_command},
		{NULL, NULL}
	};

	i = 0;
	while (builtin_command[i].name != NULL)
	{
		if (strcmp(cmd[0], builtin_command[i].name) == 0)
		{
			status = builtin_command[i].exec_builtin(cmd);
			return (status);
		}
		i++;
	}
	return (0);
}

/**
 * error - Checks if a builtin fails and outputs
 * the error message
 *
 * @status: Status of the builtin function
 * @program: Name of the program
 *
 * Return: Error status
 */
int error(int status, char *program)
{
	char *message = NULL;

	/* exit error */
	if (status == 2)
	{
		message = "too many argument";

		write(STDOUT_FILENO, program, strlen(program));
		write(STDOUT_FILENO, ": exit: ", 8);
		write(STDOUT_FILENO, message, strlen(message));
		write(STDOUT_FILENO, "\n", 1);
		return (status);
	}

	return (1); /* Base status */
}

int env_command(char **cmd)
{
	int i;
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	Mem_free_check(cmd);
	return (0);
}
