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
 * exit_builtin - Handles the exit built-in command and frees resources
 * @args: Array of tokenized arguments
 * @line: Allocated input line to be freed
 * @last_status: Exit status of the previous command
 * Return: 1 if exit was handled, 0 otherwise
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
	char *args[1024], *token, *executable = NULL;
	static int last_status;

	token = strtok(line, " \t\r\n");
	while (token && i < 1023)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	if (!args[0] || exit_builtin(args, line, last_status))
		return (last_status);

	if (strchr(args[0], '/'))
		executable = (access(args[0], X_OK) == 0) ? strdup(args[0]) : NULL;
	else
		executable = find_path(args[0]);

	if (!executable)
	{
		fprintf(stderr, "%s: %u: %s: not found\n", prog_name, line_count, args[0]);
		return (last_status = 127);
	}
	pid = fork();
	if (pid == -1)
		return (perror("Error"), free(executable), last_status = 1);
	if (pid == 0 && execve(executable, args, environ) == -1)
		perror(prog_name), free(executable), _exit(127);

	wait(&status);
	free(executable);
	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	return (last_status);
}
