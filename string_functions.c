#include "shell.h"

/**
 * _strdup - function that duplicates string with allocated memory
 *
 * @string: The string to duplicate
 *
 * Return: A pointer to the duplicate string
 */
char *_strdup(const char *string)
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
	string = string - L;
	P = malloc(sizeof(char) * (L + 1));
	if (P == NULL)
		return (NULL);
	for (i = 0; i <= L; i++)
		P[i] = string[i];

	return (P);
}

/**
 * _strcmp - function that compares two strings
 *
 * @s1: first input
 * @s2: 2nd input
 *
 * Return: 1 if true, 0 if false
 */

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
	str1++;
	str2++;
	}

	return *(unsigned char *)str1 - *(unsigned char *)str2;
}

/**
 * _strlen - function that returns lenght of a string
 *
 *@s : input
 *
 * Return: Length of the string
 */
int _strlen(const char *str)
{
	const char *s = str;
	int length = 0;
	while (*s)
	{
	length++;
	s++;
	}
	return length;
}
/**
 * *_strcat - function that concatenates two strings
 * @dest: pointer to destination input
 * @src: source pointer
 * Return: pointer resulting of @dest
 */
char *_strcat(char *dest, const char *src)
{
	char *temp = dest;

	while (*dest != '\0')
	{
	dest++;
	}

	while (*src != '\0')
	{
	*dest = *src;
	dest++;
	src++;
	}
    *dest = '\0';

    return temp;
}

/**
 * _strcpy - function that copies a string from @dest to @src
 *
 * @dest: The destination to copy to
 * @src: The source to copy from
 *
 * Return: pointer to @dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *temp = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return temp;
}
