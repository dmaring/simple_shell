#include "shell.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: size in bytes of allocated space for ptr
 * @new_size: new size in bytes of the new memory block
 * Return: void
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pointer;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	pointer = malloc(new_size);
	if (!pointer)
		return (NULL);
	if (old_size < new_size)
		old_size = old_size;
	else
		old_size = new_size;
	while (old_size--)
		pointer[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pointer);
}
