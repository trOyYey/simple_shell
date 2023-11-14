#include "shell.h"

/**
 * Mem_free_check - Free the allocated memory
 * Return: Void
 */

void Mem_free_check(char **cmd)
{
	int i;

	if (!cmd)
		return;
	for (i = 0; cmd[i]; i++)
	{
		free(cmd[i]);
       		cmd[i] = NULL;
	}
	free(cmd), cmd = NULL;
}
