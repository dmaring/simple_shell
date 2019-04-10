#include "shell.h"

/**
 * main - entrypoint to simple_shell
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	size_t n = 0;
	char *lineptr;
	char **command;
	int gl, cmd_count = 0;
	(void)argc;
	(void)env;

	signal(SIGINT, sigintHandler);
 	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "$ ", 2);

		lineptr = NULL;
		cmd_count++;

		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			free(lineptr);
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			exit(0);
		}

		/* if string is just a newline character */
		if (lineptr[0] == '\n')
		{
			free(lineptr);
			continue;
		}

		command = split_line(lineptr);
		if (command == NULL)
			continue;

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
		/* what is fp for ?? maybe just put all of this in _execute? */
		_execute(argv, command, cmd_count);
	}
	return (0);
}

void _execute(char *argv[], char **command, int cmd_count)
{
		pid_t childpid;
		int status;
		char *shcmd;

		childpid = fork();
		if (childpid == -1)
		{
			perror("Child process failed.");
			exit(EXIT_FAILURE);
		}
		/* child proccess do this */
		if (childpid == 0)
		{

			signal(SIGINT, SIG_DFL);


			/* _which will get full path of command */
			if (*command[0] != '/')
				/* why assign command[0] to fp */
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
}

/**
 * sigintHandler - handles Ctrl+C
 * @signo: signal to handle
 * Return: void
 */

void sigintHandler(int signo)
{
    signal(SIGINT, sigintHandler);
    (void)signo;
    _puts("\n$ ");
}
