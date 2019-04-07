#include "shell.h"

/**	
 * main - entrypoint to simple_shell
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	pid_t childpid;
	size_t n = 0;
	char *lineptr = NULL;
	char *arv[2];
	char **command;
	char *const environ[] = {NULL};
	int gl;

	int status, x;

	(void)argc;
	(void)argv;
	(void)env;

	while (1)
	{
		write(STDERR_FILENO, "$ ", 2);

		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			_putchar('\n');
			return (0);
		}

//		command = split_line(lineptr);
//		if (!command[0])
//		{
//			free(lineptr);
//			free(command);
//			continue;
//		}

		if (_strcmp(lineptr, "exit\n") == 0)
		{
				exit(0);
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
			if (execve(arv[0], arv, NULL) < 0)
			{
				perror(arv[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
