#include "shell.h"

/**
 * main - entry point of the simple shell
 * @argc: argument count
 * @argv: argument vector, argv[0] is the shell's invocation name
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *line;
	unsigned int line_count = 0;

	(void)argc;

	while (1)
	{
		display_prompt();

		line = read_command();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		line_count++;
		execute_command(line, argv[0], line_count);

		free(line);
	}

	return (0);
}
