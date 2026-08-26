#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line;
	unsigned int line_count = 0;

	(void)ac;

	while (1)
	{
		line_count++;
		display_prompt();
		line = read_command();
		if (line == NULL)
			break;

		execute_command(line, av[0], line_count);
		free(line);
	}

	return (0);
}
