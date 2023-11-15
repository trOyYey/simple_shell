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

int run_execve(char **cmd, char **argv, int index);
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

int getTokenLength(char *input_line, const char *delim);

#endif

