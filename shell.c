#include "shell.h"

/**
 * display_prompt - Displays the prompt symbol if in interactive mode
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_command - Reads a line of input from stdin using getline
 * Return: Pointer to the buffer containing the line, or NULL on EOF/error
 */
char *read_command(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

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
 * exit_builtin - Handles the exit built-in command and frees resources
 * @args: Array of tokenized arguments
 * @line: Allocated input line to be freed
 * @last_status: Exit status of the previous command
 * Return: 1 if exit was handled (terminates program), 0 otherwise
 */
int exit_builtin(char **args, char *line, int last_status)
{
	if (args[0] && strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(last_status);
	}
	return (0);
}

/**
 * execute_command - Resolves PATH, ensures safety checks, and runs processes
 * @line: Command line input
 * @prog_name: Name of the executable (argv[0])
 * @line_count: Current command line number for error reporting
 * Return: Exit status of the command
 */
int execute_command(char *line, char *prog_name, unsigned int line_count)
{
	pid_t pid;
	int status, i = 0;
	char *args[1024];
	char *token;
	char *executable = NULL;
	static int last_status = 0;

	token = strtok(line, " \t\r\n");
	while (token != NULL && i < 1023)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return (last_status);

	if (env_builtin(args))
		return (0);

	if (exit_builtin(args, line, last_status))
		return (last_status);

	if (strchr(args[0], '/') != NULL)
	{
		if (access(args[0], X_OK) == 0)
			executable = strdup(args[0]);
	}
	else
	{
		executable = find_path(args[0]);
	}

	if (!executable)
	{
		fprintf(stderr, "%s: %u: %s: not found\n", prog_name, line_count, args[0]);
		last_status = 127;
		return (last_status);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(executable);
		last_status = 1;
		return (last_status);
	}

	if (pid == 0)
	{
		if (execve(executable, args, environ) == -1)
		{
			perror(prog_name);
			free(executable);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		free(executable);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return (last_status);
}
