#include "shell.h"


/**
 * main - main function entry point
 *
 * @ac: argument count
 * @program: program name
 *
 * Return: 0 (Success)
 */

int main(int ac, char **program)
{
	char *input = NULL;
	char **cmd = NULL;

	(void)ac; /* unused */

	while (true)
	{
		int status = 0;

		input = read_input(&status);

		/* Handles enter key */
		if (status == 1)
		{
			free(input);
			continue;
		}

		if (input == NULL)
		{
			/* handle non interactive mode and EOF condition */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}

		cmd = get_token(input);
		if (!cmd)
			continue;

		status = run_builtin(cmd); /* executes builtin command */

		/* error with builtin commands */
		if (error(status, *program) == status)
			continue;

		status = run_execve(cmd, program); /* executus external programs */
	}
}
