#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

extern char **environ;

typedef struct
{
	char *name;
	int (*exec_builtin)(char *arg[]);

}Command;

int run_execve(char **cmd, char **argv);

char *read_input(int *status);

char **get_token(char *input_line);

void Mem_free_check(char **cmd);

char *_strdup(const char *str);

int _strcmp(char *s1, char *s2);

int _strlen(char *s);

char *_strcat(char *dest, char *src);

char *_strcpy(char *dest, char *src);

int getTokenLength(char *input_line, const char *delim);

int exit_command(char *arg[]);

int run_builtin(char **cmd);

#endif
