#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void display_prompt(void);
char *read_command(void);
void execute_command(char *line, char *prog_name, unsigned int line_count);

#endif /* SHELL_H */
