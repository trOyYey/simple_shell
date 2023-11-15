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
int exit_command(char *cmd[], char *program, int index)
{
	int number;
	const int length = 6;
	/* Contains exit status */
	if (cmd[1])
	{
		number = _atoi(cmd[1]);
		if (number < 0)
		{
			/* failed */
			char *message = "Illegal number";
			char *str;

			write(STDOUT_FILENO, program, strlen(program));
			str = toString(index); /* convert to string */

			write(STDOUT_FILENO, ": ", 2);
			write(STDOUT_FILENO, str, strlen(str));
			free(str);

			write(STDOUT_FILENO, ": exit: ", 8);
			write(STDOUT_FILENO, message, strlen(message));

			write(STDOUT_FILENO, ": ", 2);
			str = toString(number); /* convert to string */

			write(STDOUT_FILENO, str, strlen(str));
			write(STDOUT_FILENO, "\n", 1);

			free(str);
			Mem_free_check(cmd);
			return (number);
		}
		Mem_free_check(cmd);
		write(1, "exit\n", length);
		exit(number);
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
 * @cmd: Tokenized commands
 * @program: Name of the program
 * @index: Index of the current command executed
 *
 * Return: executes the builtin, 0 if commands
 * entered does not match any builtin specified
 */
int run_builtin(char **cmd, char *program, int index)
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
int env_command(char **cmd, char *program, int index)
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
