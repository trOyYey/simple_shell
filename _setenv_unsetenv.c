#include "shell.h"

/*
 * _setenv - mimics setenv
 * @name: variable name
 * @val: variable value
 * @overwrite: 1 for overwrite and 0 to do nothing
 * Return: 0 on succ, minus number if not
 */

int _setenv(const char *name, const char *val, int overwrite)
{
	int i = 0, len = 0;
	char *tmp_variable;

	if (!name || !val)
		return (-1);
	while (environ[i])
	{
		len = _strlen(name);
		if (strncmp(environ[i], name, len) == 0)
		{
			if (overwrite)
			{
				tmp_variable = malloc(_strlen(name) + _strlen(val) + 2);
				_strcpy(tmp_variable, name);
				_strcat(tmp_variable, "=");
				_strcat(tmp_variable, val);
				environ[i] = tmp_variable;
				free(tmp_variable);
				return (0);
			}
			return (0);
		}
		i++;
	}
	tmp_variable = malloc(_strlen(name) + _strlen(val) + 2);
	_strcpy(tmp_variable, name);
	_strcat(tmp_variable, "=");
	_strcat(tmp_variable, val);
	environ[i] = tmp_variable;
	environ[i + 1] = NULL;
	return (0);
}

/*
 * setenv_command - function that takes name and variable from 2d array token
 * @cmd: tokenized string in 2d array
 * Return: 0 on success -1 on error
 */
int setenv_command(char **cmd, const char *program, int index)
{
	const char *variable_name = cmd[1], *variable_value = cmd[2];
	char input_error[] = "Invalid input format for setenv.\n";
	char setenv_error[100] = "Failed to set environment variable %s\n";

	(void)*program;
	(void)index;

	if (cmd[0] == NULL || cmd[1] == NULL || cmd[2] == NULL)
	{
		write(STDERR_FILENO, input_error, _strlen(input_error));
		return (-1);
	}

	if (_setenv(variable_name, variable_value, 1) != 0)
	{
		write(STDERR_FILENO, setenv_error, _strlen(setenv_error));
		return (-1);
	}
	Mem_free_check(cmd);
	return (0);
}
