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
int _strcmp(const char *str1, const char *str2);
int _strlen(const char *str);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strend(const char *delm, int token_position);
char *c_strtok(char *cpy, const char *delm);
int _strncmp(const char *dest, char *source, int counter);


/* path handling functions */
void print_error(char *name, char *cmd, int index);
void string_reverse(char *s, int l);
char *_itoa(int N);
char *get_path(char *cmd);
char *_getenv(char *var);

int getNumLength(int number);

int isBuiltin(const char *);
/* setenv and unsetenv */
int _setenv(const char *name, const char *val, int overwrite);
int setenv_command(char **cmd, const char *program, int index);

int notValid(const char *);
char *toString(int);

ssize_t _getline(char **lineptr, size_t *n,
				 FILE * stream);

ssize_t handle_status(char **lineptr, ssize_t read_bytes,
					 ssize_t bytes_read);

void handle_exit_status(char **, int, int);

 ssize_t readFromStdin(char **lineptr, size_t *n, int fd);

int findNewLine(const char buf[], int position, short *status);

ssize_t readFromStreams(char **lineptr, size_t *n, int fd);

int handle_EOF(size_t bytes_read);
#endif
