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

	(void)argc;
	(void)argv;
	(void)env;

	while (1)
	{
		_putchar('$');
		_putchar(' ');

		getline(&lineptr, &n, stdin);

		if (lineptr == NULL)
		{
			perror("Getline failed");
			continue;
		}
		arv[0] = *lineptr;
		arv[1] = NULL;

		childpid = fork();


		if (childpid == -1)
		{
			perror("Child process failed.");
			continue;
		}
		if (childpid == 0)
		{
			execve(arv[0], arv, environ);
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
