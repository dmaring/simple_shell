#include "shell.h"

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
	write(STDERR_FILENO, av[0], _strlen(av[0]));
	_putchar(':');
	_putchar(' ');
	write(STDERR_FILENO, "command not found\n", 18);
}
