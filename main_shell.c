#include "shell.h"

/**
 * main - main function entry point
 * @ac: argument count
 * @argv: arguments
 * Return:
 */

int main(int ac, char **argv)
{
	char *input = NULL, **cmd = NULL;
	int status = 0, index = 0;


	(void)ac; /* unused */

	while (1)
	{
		input = read_input();
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}
		index++;
		cmd = get_token(input);
		if (!cmd)
			continue;

		status = run_execve(cmd, argv, index);
	}
}
