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
	char *input = NULL, **cmd = NULL;
	int status = 0, index = 0;

	(void)ac; /* unused */

	while (true)
	{
		input = read_input();
		if (input == NULL)
		{
			/* Handle non interactive mode and EOF condition */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);

			return (status);
		}
		index++;
		cmd = get_token(input);
		if (!cmd)
			continue;

		parseDollarSign(cmd); /* Expand environment variables */

		/* Execute command */
		if (isBuiltin(*cmd))
			status = run_builtin(cmd, *program, index, status); /* builtins */
		else
			status = run_execve(cmd, *program, index); /* External program */


		cmd = NULL;
	}
}
