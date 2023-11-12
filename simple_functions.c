#include "shell.h"

int Prompt_(void)
{
	size_t N;
	char *Buffer = NULL;

	printf("Terminal: Write anything");
	getline(&Buffer, &N, stdin);
	printf("you wrote %s\n", Buffer);
	free(Buffer);
	return (Buffer);
}

/**
 * strtok_ - function that splits string
 * Return:
 */

int main()
{
	char str[] = 

char *strtok_(char *str, const char *delim)
{

