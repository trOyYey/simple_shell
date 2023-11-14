#include "shell.h"

/**
 * *_getenv - function that works like getenv
 * @var: char
 * Return: char
 */

char *_getenv(char *var)
{
	int itr;
	char *cpy, *code, *eval, *ENV;

	for (itr = 0; environ[itr]; itr++)
	{
		cpy = _strdup(environ[itr]);
		code = strtok(cpy, "=");
		if (_strcmp(code, var) == 0)
		{
			eval = strtok(NULL, "\n");
			ENV = _strdup(eval);
			free(cpy);
			return (ENV);
		}
		free(cpy), cpy = NULL;
	}
	return (NULL);
}

/**
 * get_path - function that finds a path
 * cmd: char
 * Return: the currect path
 */

char *get_path(char *cmd)
{
	char *env_path, *all_cmd, *tmp_path;
	int i;
	struct stat info;

	for (i = 0; cmd[i]; i++)
	{
		if (cmd[i] == '/')
		{
			if (stat(cmd, &info) == 0)
				return(_strdup(cmd));
			return (NULL);
		}
	}
	env_path = _getenv("PATH");
	if (!env_path)
		return (NULL);

	tmp_path = strtok(env_path, ":");
	while (tmp_path)
	{
		all_cmd = malloc(_strlen(tmp_path) + _strlen(cmd) + 2);
		if (all_cmd)
		{
			_strcpy(all_cmd, tmp_path);
			_strcat(all_cmd, "/");
			_strcat(all_cmd, cmd);
			if (stat(all_cmd, &info) == 0)
			{
				free(env_path);
				return (all_cmd);
			}
			free(all_cmd), all_cmd = NULL;
			tmp_path = strtok(NULL, ":");
		}
	}
	free(env_path);
	return (NULL);
}
