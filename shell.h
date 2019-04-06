#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

char *_itoa(int n, char *s);
char *read_line(void);
char **split_line(char *line);
char *str_concat(char *s1, char *s2);
char *_strdup(char *s);
char *_strstr(char *haystack, char *needle);

int _atoi(char *s);
int _cd(char **args);
int _help(char **args);
int _launch(char **args);
int _putchar(char c);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);

void _loop(void);
void rm_nl(char **s);

#endif /*__SHELL_H__*/
