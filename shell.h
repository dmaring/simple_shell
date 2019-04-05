#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

char *str_concat(char *s1, char *s2);
char *_strdup(char *s);
char *_strstr(char *haystack, char *needle);

int _strlen(char *s);
int _strcmp(char *s1, char *s2);

#endif /*__SHELL_H__*/
