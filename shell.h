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

enum constant { exit_code = 5 };

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
	int (*exec_builtin)(char *[], const char *, int);

} Command;

char **get_token(char *);

void Mem_free_check(char **);

char *_strdup(const char *);

int _strcmp(char *, char *);

int _strlen(char *);

char *_strcat(char *, char *);

char *_strcpy(char *, char *);

int getTokenLength(char *, const char *);

int exit_command(char *[], const char *, int);

int env_command(char *[], const char *, int);

int run_builtin(char **, const char *, int, int);

int _atoi(char *);

int run_execve(char **, char *, int);

char *read_input(void);

char **get_token(char *input_line);

void Mem_free_check(char **cmd);
char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

/* path handling functions */
void print_error(char *name, char *cmd, int index);
void string_reverse(char *s, int l);
char *_itoa(int N);
char *get_path(char *cmd);
char *_getenv(char *var);

int getNumLength(int number);

int isBuiltin(const char *);


int notValid(const char *);
char *toString(int);

void handle_exit_status(char **, int, int);
#endif
