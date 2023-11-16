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
			/* handle non interactive mode and EOF condition */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}
		index++;
		cmd = get_token(input);
		if (!cmd)
			continue;

		if (isBuiltin(*cmd))
			/* executes builtin command */
			status = run_builtin(cmd, *program, index, status);
		else
			status = run_execve(cmd, *program, index); /* execute external program */
	}
}
