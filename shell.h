#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ILLNUM 227

typedef struct cmd
{
	int argc;
	char **argv;
	char **av;
	int cmd_count;
} cmd;

typedef struct envvar
{
	char *varname;
	struct envvar *next;
} envvar_t;

extern char **environ;

envvar_t *add_env_node(envvar_t **head, char *varname);

char *_itoa(int n, char *s);
char *read_line(void);
char **split_line(char *line);
char *str_concat(char *s1, char *s2);
char *_strdup(char *s);
char *_strstr(char *haystack, char *needle);
char *_which(envvar_t **env, char *filename);
char *_getenv(envvar_t **env, char *name);
char **linked_to_array(envvar_t **head);

size_t listint_len(envvar_t *h);
double _atoi(char *s);
int _cd(char *path);
int _help(char **args);
int _launch(char **args);
int _putchar(char c);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int word_count(char *s);
int build_env_list(envvar_t **head, char **env);
int free_env_list(envvar_t *head);

void *_calloc(unsigned int nmemb, unsigned int size);
void _env(envvar_t *s);
void _execute(char *argv[], char **command, int cmd_count, envvar_t **env);
void free_ptr(char **ptr);
void _loop(void);
void _puts(char *s);
void rm_nl(char **s);
void _error(char **prog, char **av, int cmd_count);
void sigintHandler(int signo);
void exit_handler(char **argv, char **command, int cmd_count);
void ffree(char **pp);

#endif /*__SHELL_H__*/
