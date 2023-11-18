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
			dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %s\n",
				program, index, cmd[1]);

			Mem_free_check(cmd);
			return (127);
		}
		Mem_free_check(cmd);
		exit(number);
	}
	/* does not contain status */
	return (exit_code);
}

/**
 * run_builtin - Checks if a command is builtin
 * and executes
 *
 * @cmd: Tokenized commands
 * @program: Name of the program
 * @index: Index of the current command executed
 * @externalStatus: Status of an external program
 *
 * Return: executes the builtin, 0 if commands
 * entered does not match any builtin specified
 */
int run_builtin(char **cmd, const char *program, int index, int externalStatus)
{
	int i, builtinStatus;

	/* map command name to it function */
	Command builtin_command[] = {
		{"exit", exit_command},
		{"env", env_command},
		{"setenv", setenv_command},
		{NULL, NULL}
	};

	i = 0;
	while (builtin_command[i].name != NULL)
	{
		if (strcmp(*cmd, builtin_command[i].name) == 0)
		{
			builtinStatus = builtin_command[i].exec_builtin(cmd, program, index);
			handle_exit_status(cmd, externalStatus, builtinStatus);

			return (builtinStatus);
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
