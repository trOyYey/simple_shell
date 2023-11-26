#include "shell.h"

char *c_strtok(char *cpy, const char *delm)
{
	static char *token_buffer;
	char *tokenst, *tokend;

	if (cpy != NULL)
		token_buffer = cpy;
	else if (token_buffer == NULL)
		return (NULL);

	tokenst = token_buffer;
	while (*tokenst != '\0' && _strend(delm, *tokenst) != NULL)
		tokenst++;
	if (*tokenst == '\0')
	{
		token_buffer = NULL;
		return (NULL);
	}

	tokend = tokenst;
	while (*tokend != '\0' && _strend(delm, *tokend) == NULL)
		tokend++;
	if (*tokend == '\0')
		token_buffer = NULL;
	else
	{
		*tokend = '\0';
		token_buffer = tokend + 1;
	}

	return (tokenst);
}

char *_strend(const char *delm, int token_position)
{
	for (; *delm != '\0'; delm++)
	{
		if (*delm == token_position)
			return ((char *)delm);
	}
	return (NULL);
}
