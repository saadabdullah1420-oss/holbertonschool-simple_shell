#include "shell.h"

/**
 * env_builtin - Prints the current environment variables
 * @args: Array of tokenized arguments
 * Return: 1 if env was handled, 0 otherwise
 */
int env_builtin(char **args)
{
	int i = 0;

	if (args[0] && strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (1);
	}
	return (0);
}

/**
 * handle_builtins - Checks and executes built-in commands like env and exit
 * @args: Array of tokenized arguments
 * @line: Allocated input line to be freed
 * @last_status: Exit status of the previous command
 * @handled: Pointer to integer flag set to 1 if built-in was handled
 * Return: Exit status or code
 */
int handle_builtins(char **args, char *line, int last_status, int *handled)
{
	*handled = 0;
	if (!args[0])
		return (last_status);

	if (env_builtin(args))
	{
		*handled = 1;
		return (0);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(last_status);
	}
	return (last_status);
}
