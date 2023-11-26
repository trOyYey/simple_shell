#include "shell.h"


/**
 * parseDollarSign - expands dollar sign indicating environment
 * variables to it value
 *
 * @cmd: The tokenized command that may contain the environment variable
 *
 * Return: void (Nothing)
 */
void parseDollarSign(char **cmd)
{
	int i = 1;

	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			char *env = cmd[i];

			cmd[i] = _getenv(env + 1);

			free(env);
		}
		i++;
	}
}
