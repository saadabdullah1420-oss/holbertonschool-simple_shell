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
int execute_command(char *line, char *prog_name, unsigned int line_count);
int exit_builtin(char **args, char *line, int last_status);
int handle_builtins(char **args, char *line, int last_status, int *handled);
int run_execve(char *executable, char **args, char *prog_name);
char *_getenv(const char *name);
char *find_path(char *command);
int env_builtin(char **args);
#endif /* SHELL_H */
