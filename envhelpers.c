#include "shell.h"

/**
 * add_env_node
 *
 *
 */
envvar_t *add_env_node(envvar_t **head, char *varname)
{
	envvar_t *new;

	new = malloc(sizeof(envvar_t));

	if (new == NULL)
		return (NULL);

	new->varname = strdup(varname);
	if (*head == NULL)
		new->next = NULL;
	else
		new->next = *head;
	*head = new;

	return(new);
}


/**
 * free_env_node
 *
 *
 */




/**
 * find_env_node
 *
 *
 */


/**
 * free_env_list
 *
 *
 */
int free_env_list(envvar_t **head)
{
	/* store head in current to preserve head */
	envvar_t *current = *head;
	/* create temp to store linked list item to be freed */
	envvar_t *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->varname);
		free(temp);
	}

	/* free(head); */

	return (1);
}

/**
 * build_env_list
 * @env: double pointer envp main argument containing env variables
 *
 * Return: 0 on success;
 */
int build_env_list(envvar_t **head, char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		add_env_node(head, env[i]);
		i++;
	}

	return(0);
}

/**
 * linked_to_array - transform linked list to list of char pointers
 * @head: double pointer to head of list
 *
 * Return: pointer to list of char pointers
 */
char **linked_to_array(envvar_t **head)
{
	char **list;
	envvar_t **a = head;
	size_t i = 0;
	size_t j = 0;

	/* count number of items in linked list */
	i = listint_len(*head);
	/* malloc list of pointers for number of items */
	list = _calloc(i, sizeof(char *) * i);

	while (*a)
	{
		/* retreive the environment variable from linked list node */
		/* strdup the env variable into double array */
		list[j] = _strdup((*a)->varname);
		j++;

		*a = (*a)->next;
	}

	return (list);
}

/**
 * listint_len - function that finds the number of elements in a linked list
 * @h: pointer to start of linked list
 *
 * Return: size_t number of elements
 */
size_t listint_len(envvar_t *h)
{
	size_t nodeCount = 0;

	while (h != NULL)
	{
		nodeCount++;
		h = h->next;
	}

	return (nodeCount);
}


/**
 * print_listint - prints all elements of a listint_t list
 * @h: pointer to head of linked list
 *
 * Return: number of nodes in the list
 */
size_t print_listint(envvar_t *h)
{
	size_t nodeCount = 0;

	while (h != NULL)
	{
		printf("%s\n", h->varname);
		nodeCount++;
		h = h->next;
	}


	return (nodeCount);
}
