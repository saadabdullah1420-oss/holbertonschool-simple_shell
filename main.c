#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (line[0] == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			execve(argv[0], argv, environ);
			perror("./hsh");
			exit(127);
		}

		wait(NULL);
	}

	free(line);
	return (0);
}
