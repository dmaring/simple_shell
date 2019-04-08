#include "shell.h"
#include <errno.h>

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
	char **command;
	char buffer[10];
	int gl;

	int status;

	(void)argc;
	(void)argv;
	(void)env;

 	while (1)
	{
		write(STDERR_FILENO, "$ ", 2);

		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			perror("getline failed\n");
			return (0);
		}

		command = split_line(lineptr);
		if (!command[0])
		{
			free(lineptr);
			free(command);
			continue;
		}

		if (_strcmp(command[0], "exit") == 0)
		{
			exit(0);
		}
		if (_strcmp(command[0], "env") == 0)
		{
//			_env();
			continue;
		}

		childpid = fork();
		if (childpid == -1)
		{
			perror("Child process failed.");
			exit(EXIT_FAILURE);
		}
		if (childpid == 0)
		{
			if (execve(command[0], command, NULL) < 0)
			{
				/* check for errno on failure */
				if (errno == 1 || errno == 2)
				{
					_error(command);
				}
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
