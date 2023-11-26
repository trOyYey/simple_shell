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
int exit_command(char **cmd, const char *program, int index)
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

			return (2);
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
		{"setenv", setenv_command},
		{"cd", cd_command},
		{"env", env_command},
		{NULL, NULL}
	};

	i = 0;
	while (builtin_command[i].name != NULL)
	{
		if (strcmp(*cmd, builtin_command[i].name) == 0)
		{
			builtinStatus = builtin_command[i].exec_builtin(cmd, program, index);
			handle_exit_status(cmd, externalStatus, builtinStatus);

			Mem_free_check(cmd);
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
	(void)cmd;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * cd_command - Change the working directory
 *
 * @cmd: The tokenized command
 * @program: The name of the program current running
 * @index: The index of the command
 *
 * Return: 0 on success and 2 on failure
 */
int cd_command(char **cmd, const char *program, int index)
{
	char *buf;
	static char *pwd;
	char *env = "OLDPWD";

	pwd = _getenv("PWD");
	/* When no argument is passed default to HOME */
	if (!cmd[1])
		cmd[1] = _getenv("HOME");
	else if (!strcmp(cmd[1], "-")) /* Handles previous directory */
		cmd[1] = _getenv(env);

	if (setenv(env, pwd, 1) == -1) /* Previous directory */
	{
		free(pwd);
		return (2);
	}
	/* Change working directory */
	if (chdir(cmd[1]) == -1)
	{
		dprintf(STDERR_FILENO, "%s: %d: cd: can't cd to directory %s\n",
				program, index, cmd[1]);
		free(pwd);
		return (2);
	}

	/* Update parent working directory */
	buf = _getcwd();
	if (!buf)
	{
		free(pwd);
		return (2);
	}
	if (setenv("PWD", buf, 1) == -1)
	{
		free(buf), free(pwd);
		return (2);
	}
	free(pwd), free(buf);

	return (0); /* success */
}

/**
 * _getcwd - Gets the current working directory
 *
 * Return: A pointer to the current working directory, NULL
 * if it fails
 */
char *_getcwd(void)
{
	int n;
	char *buf, *temp;

	n = 25;
	buf = malloc(sizeof(char) * n);

	if (!buf)
		return (NULL);

	/* Not enough size to store path so increment */
	while (!getcwd(buf, n))
	{
		n *= 2;
		temp = realloc(buf, sizeof(char) * n);

		if (!temp)
		{
			free(buf);
			return (NULL);
		}

		buf = temp;
	}
	/* Perfect size to store path in buf */
	if (!getcwd(buf, n))
	{
		free(buf);
		return (NULL);
	}

	return (buf);
}
