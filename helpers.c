 #include "shell.h"

/**
 * rm_nl - remove the last character newline from string
 * @str: double pointer to string
 *
 * Return: 0 on success
 */
void rm_nl(char **lineptr)
{
	char *ptr;
	int i;

	ptr = *lineptr;

	i = 0;
	while (ptr[i] != '\n')
		i++;
	ptr[i] = '\0';
}
/**
 * _getenv - get the value of an environment variabl
 * @key: name of environment variable
 *
 * Return: pointer to string value of @key
 */
char *_getenv(const char *name)
{
	return (char *)name;
}

/**
 * _which - return absolute path of passed command or script
 *
 *
 * Return: character string of absolute path to command or script
 */
char *_which(char *filename)
{
	char *path;
	char *token;
	char *fullpath;
	struct stat st;

	filename = str_concat("/", filename);
	path = _getenv("PATH");

	token = strtok(path, ":");

	while (token != NULL)
	{
		fullpath = str_concat(token, filename);
		if (stat(fullpath, &st) == 0)
			return (fullpath);

		token = strtok(NULL, ":");
	}

	return (path);

}
