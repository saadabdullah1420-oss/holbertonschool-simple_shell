#include "shell.h"

/**
 * copy_string - Allocates memory and copies a string into it
 * @src: The string to copy
 *
 * Return: Malloc'd copy of src, or NULL on failure
 */
char *copy_string(char *src)
{
	char *dest;

	dest = malloc(strlen(src) + 1);
	if (dest == NULL)
		return (NULL);
	strcpy(dest, src);
	return (dest);
}

/**
 * find_path - Searches PATH directories for an executable command
 * @command: The command to search for (may or may not contain '/')
 *
 * Return: Malloc'd string with the full usable path, or NULL if not found
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (copy_string(command));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = copy_string(path_env);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
