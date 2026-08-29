#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
extern char **environ;

void display_prompt(void);
char *read_command(void);
void execute_command(char *line, char *prog_name, unsigned int line_count);

char *_getenv(const char *name);
char *find_path(char *command);

#endif /* SHELL_H */
