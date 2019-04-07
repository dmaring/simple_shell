#include "shell.h"

/*
 * main - entrypoint to simple_shell
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	pid_t childpid;
	size_t n = 0;
	int  status;
	char *lineptr = NULL;
	char *arv[2];
	char *const environ[] = {NULL};
	int gl;

	(void)argc;
	(void)argv;
	(void)env;

	while (1)
	{
		_puts("$ ");

		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			_putchar('\n');
			return (0);
		}

		if (_strcmp(lineptr, "env\n") == 0)
		{
			_env();
			continue;
		}

		rm_nl(&lineptr);
		arv[0] = lineptr;
		arv[1] = NULL;

		childpid = fork();
		if (childpid == -1)
		{
			perror("Child process failed.");
			exit(1);
		}
		if (childpid == 0)
		{
			execve(arv[0], arv, NULL);

		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
