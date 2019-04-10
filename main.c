#include "shell.h"

/**
 * main - entrypoint to simple_shell
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	size_t n = 0;
	char *lineptr = NULL;
	char **command;
	int gl = 0, cmd_count = 0;
	(void)argc, (void)env;

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "$ ", 2);
		cmd_count++;
		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			_putchar('\n');
			free(lineptr);
			return (0);
		}
		if (lineptr[0] == '\n')
		{
			continue;
		}
		command = split_line(lineptr);
		if (_strcmp(command[0], "exit") == 0)
			exit_handler(command[1]);
		if (_strcmp(command[0], "env") == 0)
		{
			_env();
			continue;
		}
		_execute(argv, command, cmd_count);
		/* free(command); */
		/* free(lineptr); */
	}
	return (0);
}

/**
 * _execute - executes commands from main function
 * @argv: argument from command line
 * @command: parsed command array
 * @cmd_count: count of commands in session
 */
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
		shcmd = command[0];

		if (*command[0] != '/')
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
 * exit_handler - handles exit
 */
void exit_handler(char *command)
{
 	/* if ((_atoi(command)) > 2147483647 || (_atoi(command)) < 0) */
	/* 	perror("ERROR"); */

	if (command == NULL)
	{
		exit(0);
	}
	else
		exit(_atoi(command));
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
