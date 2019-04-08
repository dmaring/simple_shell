#include "shell.h"
#include <errno.h>

extern char **environ;

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @s: string to print
 * Return: void
 */
void _puts(char *s)
{
	while (*s)
	{
		_putchar(*s);
		s++;
	}
}

/**
 * _env - prints the current environment
 * Return: void
 */
void _env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDIN_FILENO, environ[i], _strlen(environ[i]));
		_putchar('\n');
		i++;
	}
}

/**
 * _error - prints error
 * @av: argument
 */
void _error(char **av)
{
	char *buffer = malloc(sizeof(char) * 10);

	write(STDERR_FILENO, av[0], _strlen(av[0]));
	_putchar(':');
	_putchar(' ');
	_puts(_itoa(errno, buffer));
	free(buffer);
	_putchar(':');
	_putchar(' ');
	if (av[1])
		{
			write(STDERR_FILENO, av[1], _strlen(av[1]));
			_putchar(':');
			_putchar(' ');
		}
	write(STDERR_FILENO, "not found\n", 10);
}
