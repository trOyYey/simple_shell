#ifndef SHELL_H
#define SHELL_H

/* System header */
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

extern char **environ;

/**
 * struct Command - A structure that maps
 * commands to it respective function implemntations
 *
 * @name: The name of the command (key)
 * @exec_builtin: The name of the function (value)
 */
typedef struct Command
{
	char *name;
	int (*exec_builtin)(char *arg[]);

} Command;

int run_execve(char **, char **);

char *read_input(int *);

char **get_token(char *);

void Mem_free_check(char **);

char *_strdup(const char *);

int _strcmp(char *, char *);

int _strlen(char *);

char *_strcat(char *, char *);

char *_strcpy(char *, char *);

int getTokenLength(char *, const char *);

int exit_command(char *[]);

int run_builtin(char **);

int _atoi(char *);

int error(int status, char *program);

#endif
