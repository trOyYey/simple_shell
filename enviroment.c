#include "shell.h"

/**
 * *_getenv - function that works like getenv
 * @var: char
 * Return: char
 */
char *_getenv(char *var)
{
	int itr;
	char *cpy, *code, *eval, *env;

	for (itr = 0; environ[itr]; itr++)
	{
		cpy = _strdup(environ[itr]);
		code = strtok(cpy, "=");
		if (_strcmp(code, var) == 0)
		{
			eval = strtok(NULL, "\n");
			env = _strdup(eval);

			free(cpy);
			return (env);
		}
		free(cpy), cpy = NULL;
	}
	return (NULL);
}

/**
 * get_path - function that finds a path
 *
 * @cmd: the command
 *
 * Return: the currect path
 */

char *get_path(char *cmd)
{
	char *env_path, *full_path, *tmp_path;
	int i;
	struct stat info;

	for (i = 0; cmd[i]; i++)
	{
		if (cmd[i] == '/')
		{
			if (stat(cmd, &info) == 0)
				return (_strdup(cmd));
			return (NULL);
		}
	}
	env_path = _getenv("PATH");
	if (!env_path)
		return (NULL);

	tmp_path = strtok(env_path, ":");
	while (tmp_path)
	{
		full_path = malloc(_strlen(tmp_path) + _strlen(cmd) + 2);
		if (full_path)
		{
			_strcpy(full_path, tmp_path);
			_strcat(full_path, "/");
			_strcat(full_path, cmd);

			if (access(full_path, X_OK) == 0)
			{
				free(env_path);
				return (full_path);
			}
			free(full_path), full_path = NULL;
			tmp_path = strtok(NULL, ":");
		}
	}
	free(env_path);
	return (NULL);
}
