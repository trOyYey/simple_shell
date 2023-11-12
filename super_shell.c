#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int i = 0, stat;
	size_t Buffer_size;
	char *Buffer = NULL, *Token, **Array;
	pid_t sub_proc_pid;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
		getline(&Buffer, &Buffer_size, stdin);
		Token = strtok(Buffer, "\t\n");
		Array = malloc(sizeof(char *) * 1024);

		while (Token)
		{
			Array[i] = Token;
			Token = strtok(NULL, "\t\n");
			i++;
		}
		Array[i] = NULL;
		sub_proc_pid = fork();

		if (sub_proc_pid == 0)
		{
			if (execve(Array[0], Array, NULL) == -1)
				perror("Error");
		}
		else
		{
			wait(&stat);
		}
		i = 0;
		free(Array);
	}
}

