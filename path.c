#include "shell.h"

/**
 * _getenv - Gets the value of an environmental variable
 * @name: Name of the environment variable
 * Return: Pointer to value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i, j;

	if (!name || !environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j] && name[j] && environ[i][j] == name[j]; j++)
			;
		if (environ[i][j] == '=' && name[j] == '\0')
			return (&environ[i][j + 1]);
	}
	return (NULL);
}

/**
 * find_path - Finds the full path of a command using the PATH variable
 * @command: Command name entered by user
 * Return: Allocated full path string, or NULL if not found
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *token, *full_path;
	struct stat st;
	int dir_len, cmd_len;

	if (!command)
		return (NULL);
	if (stat(command, &st) == 0 && (command[0] == '/' || command[0] == '.'))
		return (strdup(command));

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	cmd_len = strlen(command);
	token = strtok(path_copy, ":");
	while (token)
	{
		dir_len = strlen(token);
		full_path = malloc(dir_len + cmd_len + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
