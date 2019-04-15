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
	char **command = NULL;
	int gl = 0, cmd_count = 0;
	(void)env;
	(void)argc;

	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "$ ", 2);
		cmd_count++;
		gl = getline(&lineptr, &n, stdin);
		/* gl -1 if getline failes */
		if (gl < 0)
		{
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			free(lineptr);
			lineptr = NULL;
			exit(errno);
		}
		/* condition where user doesnt entire commands */
		if ( word_count(lineptr) == 0)
		{
			continue;
		}
		/* command will hold list of arguments passed in lineptr */
		command = split_line(lineptr);
		free(lineptr);
		lineptr = NULL;
		/* TODO function search builtins and return func ptr */
		if (_strcmp(command[0], "exit") == 0)
		{
			exit_handler(argv, command, cmd_count);
			continue;
		}
		if (_strcmp(command[0], "env") == 0)
		{
			_env();
			continue;
		}
		/* execute arguments passing in calling process \
		   command list, number of words in command */
		_execute(argv, command, cmd_count);
		/* free(command);*/

		/* free(lineptr); */
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
/* 	char **new_cmd = 0; */


	childpid = fork();
	if (childpid == -1)
	{
		free(argv);
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
			/* check for errno 2 on failure */
			if (errno == 2)
			{
				_error(argv, &shcmd, cmd_count);
				ffree(command);
				exit(EXIT_SUCCESS);
			}
			ffree(command);
			exit(1);
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
		_error(prog, command, cmd_count);
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
	write(STDERR_FILENO, "\n$", 3);
	fflush(stdout);
}
