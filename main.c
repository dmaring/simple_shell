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
	char *lineptr, *shcmd;
	char **command;
	int cmd_count, gl, status;

	(void)argc;
//	(void)argv;
	(void)env;

	signal(SIGINT, sigintHandler);
	cmd_count = 0;
 	while (1)
	{
		write(STDERR_FILENO, "$ ", 2);

		lineptr = NULL;
		gl = getline(&lineptr, &n, stdin);
		cmd_count++;
		if (gl == EOF)
		{
			_putchar('\n'), fflush(NULL), exit(0);
		}

		/* if string is just a newline character */
		if (lineptr[0] == '\n')
		{
			free(lineptr);
			continue;
		}

		command = split_line(lineptr);
//		if (!command)
//			continue;

		if (_strcmp(command[0], "exit") == 0)
		{
			if (command[1] == NULL)
				exit(0);
			else
				exit(_atoi(command[1]));
		}
		if (_strcmp(command[0], "env") == 0)
		{
			_env();
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
			signal(SIGINT, SIG_DFL);
			shcmd = command[0];

			/* _which will get full path of command */
			command[0] = _which(command[0]);
			if (execve(command[0], command, NULL) < 0)
			{
				/* check for errno 2 on failure */
				if (errno == 2)
				{
					_error(argv, &shcmd, cmd_count);
					exit(127);
				}
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
		free(command);
		free(lineptr);
	}
	return (0);
}

/**
 * sigintHandler - handles Ctrl+C
 * @signo: signal to handle
 * Return: void
 */

void sigintHandler(int signo)
{
    signal(SIGINT, sigintHandler);
    _puts("\n$ ");
}
