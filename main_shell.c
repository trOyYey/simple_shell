#include "shell.h"

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
		if (!cmd)
			continue;

		status = run_execve(cmd, program);
	}
}
