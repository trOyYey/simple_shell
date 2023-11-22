#include "shell.h"

/*
 * _setenv - mimics setenv
 * @name: variable name
 * @val: variable value
 * @overwrite: 1 for overwrite and 0 to do nothing
 * Return: 0 on succ, minus number if not
 */

char *_setenv(const char *name, const char *val, int overwrite)
{
	int i;
	char *tmp_variable;

	if (!name || !val)
		return (NULL);

	tmp_variable = malloc(_strlen(name) + _strlen(val) + 2);

	if (tmp_variable == NULL)
		return (NULL);

	/* store the values */
	_strcpy(tmp_variable, name);
	_strcat(tmp_variable, "=");
	_strcat(tmp_variable, val);
	_strcat(tmp_variable, "\0"); /* terminate */

	i = 0;
	while (environ[i])
	{
		const char *strLength = strchr(environ[i], '=');

		if (strncmp(environ[i], name, strLength - environ[i]) == 0)
		{
			if (overwrite)
			{
				environ[i] = (tmp_variable);
				return (tmp_variable);
			}

			return (tmp_variable); /* overwrite is 0 */
		}
		i++;
	}

	environ[i] = (tmp_variable);
	environ[i + 1] = NULL;
	return (tmp_variable);
}

/*
 * setenv_command - function that takes name and variable from 2d array token
 * @cmd: tokenized string in 2d array
 * Return: 0 on success -1 on error
 */
int setenv_command(char **cmd, const char *program, int index)
{
	const char *variable_name = cmd[1], *variable_value = cmd[2];
	int failure = 7;
	char *alloc;


	/* unused */
	(void)*program;
	(void)index;

	if (cmd[0] == NULL || cmd[1] == NULL || cmd[2] == NULL)
	{
		char input_error[] = "Invalid input format for setenv.\n";
		write(STDERR_FILENO, input_error, _strlen(input_error));
		return (failure);
	}

	alloc = _setenv(variable_name, variable_value, 1);

	if (!alloc)
	{
		char setenv_error[100] = "Failed to set environment variable %s\n";
		write(STDERR_FILENO, setenv_error, _strlen(setenv_error));
		return (failure);
	}

	return (0);
}
