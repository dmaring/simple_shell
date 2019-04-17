#include "shell.h"

/**
 * main - entrypoint to simple_shell
 *
 * @ac: number of arguments
 * @argv: commands and arguments
 *
 * Return: 0 on success
 */
int main(int __attribute__((unused))ac, char *argv[])
{
	size_t n = 0;
	char *lineptr = NULL;
	char **command = NULL;
	int gl = 0, cmd_count = 0;

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "$ ", 2);
		cmd_count++;
		gl = getline(&lineptr, &n, stdin);
		if (gl < 0)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(lineptr);
			exit(0);
		}
		if (word_count(lineptr) == 0)
			continue;
		command = split_line(lineptr);
		free(lineptr);
		lineptr = NULL;
		if (_strcmp(command[0], "exit") == 0)
		{
			exit_handler(argv, command, cmd_count);
			continue;
		}
		if (_strcmp(command[0], "env") == 0)
		{
			_env();
			ffree(command);
			continue;
		}
		_execute(argv, command, cmd_count);
	}
	free(lineptr);
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
	char *shcmd = NULL;

	childpid = fork();
	if (childpid == -1)
	{
		perror("Child process failed.");
		exit(EXIT_FAILURE);
	}
	/* child proccess do this */
	if (childpid == 0)
	{
		/* ignore ctrl c SIGINT */
		signal(SIGINT, SIG_DFL);
		/* _which will get full path of command */
		shcmd = command[0];
		/* handle case of entering abs path for command */
		if (*command[0] != '/')
			command[0] = _which(command[0]);
		/* check for failure of execve */
		if (execve(command[0], command, NULL) < 0)
		{
			if (errno == 2)
			{
				_error(argv, &shcmd, cmd_count);
				ffree(command);
				free(shcmd);
				_exit(1);
			}
			ffree(command);
			free(shcmd);
			_exit(1);
		}
	}
	else
	{
		wait(&status);
		ffree(command);
	}
}

/**
 * exit_handler - handles exit
 * @prog: program
 * @command: exit number
 * @cmd_count: current command count
 */
void exit_handler(char **prog, char **command, int cmd_count)
{
	long int a = 0;

	a = command[1] ? _atoi(command[1]) : 0;
	if (command[1] == NULL)
	{
		ffree(command);
		exit(0);
	}

	if (a > 2147483647 || a < 0)
	{
		errno = 0;
		_error(prog, command, cmd_count);
	}
	else
	{
		ffree(command);
		exit(a);
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
	write(STDERR_FILENO, "\n$ ", 3);
	fflush(stdout);
}
