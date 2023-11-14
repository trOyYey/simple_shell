#include "shell.h"

/**
 * main - main function entry point
 * @ac: argument count
 * @argv: arguments
 * Return:
 */

int main(int ac, char **argv)
{
	char *input_line = NULL;
	char **cmd = NULL;
	int  status = 0;
	(void)ac;

	while (1)
	{
		input_line = analyze_line();
		if (input_line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}
		cmd = get_token(input_line);
		if (!cmd)
			continue;
		status = run_execve(cmd, argv);
	}
}
