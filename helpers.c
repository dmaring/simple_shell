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
 * @name: input string
 *
 * Return: pointer to string value of @key
 */
char *_getenv(char *name)
{
	int i = 0;

	while (environ[i])
	{
		char *haystack = environ[i];
		char *needle = name;

		while (*haystack == *needle)
		{
			haystack++;
			needle++;
		}
		if (*needle == '\0')
			return (haystack + 1);

		i++;
	}
	return (NULL);
}

/**
 * _which - return absolute path of passed command or script
 *
 *
 * Return: character string of absolute path to command or script
 */
char *_which(char *filename)
{
	char *path = NULL;
	char *buf = NULL;
	char *wd = NULL;
	char *token = NULL;
	char *fullpath = NULL;
	size_t n = 0;
	struct stat st;

	filename = str_concat("/", filename);


	path = _getenv("PATH");
	if (path[0] == ':')
	{
		wd = getcwd(buf, n);
		fullpath = str_concat(wd, filename);
		free(wd);
		if (stat(fullpath, &st) == 0)
		{
			free(filename);
			return (fullpath);
		}
		else
			free(fullpath);
	}

	token = strtok(path, ":");

	while (token != NULL)
	{
		fullpath = str_concat(token, filename);
		if (stat(fullpath, &st) == 0)
		{
			free(filename);
			return (fullpath);
		}
		token = strtok(NULL, ":");
	}

	free(fullpath);
	free(filename);
	return (NULL);
}

void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned int i;
	char *s;

	if (nmemb == 0 || size == 0)
		return (NULL);
	s = malloc(nmemb * size);

	if (s == NULL)
		return (NULL);
	for (i = 0; i < nmemb * size; i++)
	{
		s[i] = 0;
	}
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
