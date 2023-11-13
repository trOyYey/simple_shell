#include "shell.h"

/**
 * *_STRDUP - function that duplicates string with allocated memory
 * @P: pointer
 * @i: int
 * @L: lenght of string
 * Return: P
 */

char *_strdup(cont char *string)
{
	char *P;
	int i, L = 0;

	if (string == NULL)
		return (NULL);
	while (*string != '\0')
	{
		L++;
		string++;
	}
	string = string - len;
	P = malloc(sizeof(char) * (len + 1));
	if (P == NULL)
		return (NULL);
	for (i = 0; i <= L; i++)
		P[i] = string[i];
	return (P);
}

/**
 * _strcmp - function that compares two strings
 * @s1: first input
 * @s2: 2nd input
 * Return: 1 if true, 0 if false
 */

int _strcmp(char *s1, char *s2)
{
	int totall = 0;

	while (*s1)
	{
		if (*s1 != *s2)
		{
			totall = ((int)*s1 - 48) - ((int)*s2 - 48);
			break;
		}
		s1++;
		s2++;
	}
	return (totall);
}

/**
 * _strlen - function that returns lenght of a string
 *@s : input
* Return: lenght of string
*/

int _strlen(char *s)
{
	int counter;

	for (counter = 0; *s != '\0'; s++)
		++counter;

	return (counter);
}

/**
 * *_strcat - function that concatenates two strings
 * @dest: pointer to destination input
 * @src: source pointer
 * Return: pointer resulting of @dest
 */

char *_strcat(char *dest, char *src)
{
	int destL = 0;
	int srcL = 0;
	int i;

	for (i = 0; dest[i] != '\0'; i++)
		destL++;
	for (i = 0; src[i] != '\0'; i++)
		srcL++;

	for (i = 0; i <= srcL; i++)
		dest[destL + i] = src[i];
	return (dest);

}

/**
 * *_strcpy - function that copies the string pointed by
*				src
*@dest: input buffer
*@src: pointed string input
 *Return: pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = -1;

	do {
		i++;
		dest[i] = src[i];
	}	while (src[i] != '\0');

	return (dest);
}

