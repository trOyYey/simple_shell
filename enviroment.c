#include "shell.h"

/**
 * *_getenv - function that works like getenv
 * @var: char
 * Return: char
 */

char *_getenv(char *variable)
{
	int itr;
	char *cpy

	for (itr = 0; environ[i]; itr++)
	{

