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
	int i, stat = 0;
	(void)ac;
	(void)argv;

	while (1)
	{
		input_line = analyze_line();
		if (input_line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (stat);
		}
		cmd = get_token(input_line);
		if (!cmd)
			continue;

		for (i = 0; cmd[i]; i++)
			printf("%s\n", cmd[i]);
	}
}
