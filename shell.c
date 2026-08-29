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
 *
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
 * execute_command - Tokenizes input line and executes command with args
 * @line: Command line input
 * @prog_name: Name of the executable (argv[0])
 * @line_count: Current command line number for error reporting
 */
void execute_command(char *line, char *prog_name, unsigned int line_count)
{
	pid_t pid;
	int status;
	int i = 0;
	char *args[1024];
	char *token, *full_path;

	token = strtok(line, " \t\r\n");
	while (token != NULL && i < 1023)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	full_path = find_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			prog_name, line_count, args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(full_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror(prog_name);
			free(full_path);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		free(full_path);
	}
}
