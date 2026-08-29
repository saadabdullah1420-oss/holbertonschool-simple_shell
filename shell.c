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
 * execute_command - Tokenizes input line and executes command with args
 * @line: Command line input
 * @prog_name: Name of the executable (argv[0])
 * @line_count: Current command line number for error reporting
 * Return: Exit status (127 on command not found, or command's exit status)
 */
int execute_command(char *line, char *prog_name, unsigned int line_count)
{
	pid_t pid;
	int status, i = 0;
	char *args[1024];
	char *token;
	char *executable;

	token = strtok(line, " \t\r\n");
	while (token != NULL && i < 1023)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return (0);

	executable = find_path(args[0]);
	if (executable == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n",
			prog_name, line_count, args[0]);
		return (127); /* Return 127 when command is not found */
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(executable);
		return (1);
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
			return (WEXITSTATUS(status));
	}
	return (0);
}
