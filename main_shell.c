#include "shell.h"

Command builtin_command[] =
{
	{"exit", exit_command},
	{NULL, NULL}
};

/**
 * main - main function entry point
 * @ac: argument count
 * @argv: arguments
 * Return:
 */

int main(int ac, char **program)
{
	char *input = NULL;
	char **cmd = NULL;
	int status;

	(void)ac; /* unused */

	while (1)
	{
		status = 0;
		input = read_input(&status);

		/* Handles enter key */
		if (status == 1)
		{
			free(input);
			continue;
		}

		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}

		cmd = get_token(input);
		input = NULL;

		if (!cmd)
			continue;

		run_builtin(cmd);

		status = run_execve(cmd, program);
	}
}

int exit_command(char *arg[])
{
	(void)arg;

	write(1, "exit\n", 6);
	exit(EXIT_SUCCESS);
}

int run_builtin(char **cmd)
{
	int i;

	i = 0;
	while (builtin_command[i].name != NULL)
	{
		if (strcmp(cmd[0], builtin_command[i].name) == 0)
			builtin_command[i].exec_builtin(cmd);

		i++;
	}

	return (0);
}
