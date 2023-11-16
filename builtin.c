#include "shell.h"

/**
 * exit_command - exit builtin command
 *
 * @cmd: tokenized commands
 * @program: Name of the program
 * @index: Index of the current command executed
 *
 * Return: exit status if the function fails
 * otherwise exit
 */
int exit_command(char *cmd[], const char *program, int index)
{
	/* Contains exit status */
	if (cmd[1])
	{
		int number = _atoi(cmd[1]);

		if (notValid(cmd[1]))
		{
			/* exit failed */
			dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %s\n", program, index, cmd[1]);

			Mem_free_check(cmd);
			return (EXIT_FAILURE);
		}
		Mem_free_check(cmd);
		exit(number);
	}
	/* does not contain status */
	Mem_free_check(cmd);
	exit(EXIT_SUCCESS);
}

/**
 * run_builtin - Checks if a command is builtin
 * and executes
 *
 * @cmd: Tokenized commands
 * @program: Name of the program
 * @index: Index of the current command executed
 *
 * Return: executes the builtin, 0 if commands
 * entered does not match any builtin specified
 */
int run_builtin(char **cmd, const char *program, int index)
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
		if (strcmp(*cmd, builtin_command[i].name) == 0)
		{
			status = builtin_command[i].exec_builtin(cmd, program, index);
			return (status);
		}
		i++;
	}
	return (0);
}

/**
 * env_command - Outputs system environmental variables
 *
 * @cmd: The tokenized command
 * @program: Name of the program
 * @index: Index of the current command executed
 *
 * Return: always 0
 */
int env_command(char **cmd, const char *program, int index)
{
	int i;

	/* unused */
	(void)program;
	(void)index;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	Mem_free_check(cmd);
	return (0);
}

/**
 * isBuiltin - Checks if a command is belongs
 * to the specified shell builtin commands
 *
 * @command: Command to check
 *
 * Return: 1 if the commands is found, 0 otherwise
 */
int isBuiltin(const char *command)
{
	int i;
	const char *builtin_cmd[] = {"exit", "env", NULL};

	i = 0;
	while (builtin_cmd[i])
	{
		if (!strcmp(builtin_cmd[i], command))
			return (1);
		i++;
	}

	return (0);
}
