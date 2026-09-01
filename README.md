# Simple Shell

A UNIX command interpreter, written in C, built as part of the Holberton /
ALX low-level programming curriculum. It reads commands from standard
input (interactively or via a pipe), resolves them against `PATH`, and
executes them — mimicking the core behavior of `/bin/sh`.

## Description

`hsh` implements a REPL (read-eval-print loop) that:

- Displays a prompt (`$ `) when running in interactive mode (i.e. when
  standard input is a terminal).
- Reads a line of input using `getline`.
- Splits the line into a command and its arguments.
- Checks for built-in commands (`env`, `exit`) before falling back to
  external programs.
- Locates external programs using the `PATH` environment variable, or
  directly if the command contains a `/`.
- Forks a child process and uses `execve` to run the program.
- Waits for the child to finish and returns its exit status.
- Repeats until `exit` is called or `EOF` (Ctrl+D) is reached.

## Files

| File          | Description                                                              |
|---------------|---------------------------------------------------------------------------|
| `main.c`      | Entry point; runs the main read/execute loop.                             |
| `shell.c`     | Prompt display, input reading, command execution, and `execve` wrapper.   |
| `builtins.c`  | Built-in commands (`env`) and the built-in dispatch helper.               |
| `path.c`      | `PATH` resolution (`find_path`) and a custom `_getenv` implementation.    |
| `shell.h`     | Header file with all function prototypes and includes.                   |
| `AUTHORS`     | List of project contributors.                                            |
| `README.md`   | This file.                                                                |

## Compilation

The shell is compiled with:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive mode

```console
$ ./hsh
$ /bin/ls
hsh main.c shell.c shell.h builtins.c path.c README.md
$ exit
$
```

### Non-interactive mode

```console
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c shell.h builtins.c path.c README.md
```

Multiple commands can also be piped in from a file:

```console
$ cat commands.txt | ./hsh
```

### Command not found

If a command cannot be resolved via `PATH` (and is not a direct or
relative path to an executable), the shell prints an error using the
same format as `sh`, but with the shell's own `argv[0]` as the program
name:

```console
$ ./hsh
$ qwerty
./hsh: 1: qwerty: not found
```

## Built-in commands

- **`env`** — Prints the current environment variables, one per line.
- **`exit`** — Exits the shell, freeing allocated memory first. (Does not
  yet support a custom exit status argument, e.g. `exit 2`.)

## Environment handling

`_getenv` is implemented from scratch (in `path.c`) to look up variables
directly in the `environ` array, without relying on the C library's
`getenv`.

## PATH resolution

`find_path` (in `path.c`) works as follows:

1. If the command contains a `/` or starts with `.`, it's treated as a
   direct or relative path and checked with `stat`.
2. Otherwise, the `PATH` variable is split on `:` and each directory is
   tried in turn (`<dir>/<command>`) until a match is found via `stat`.
3. If no match is found, `NULL` is returned and the shell reports
   `not found`.

## Error handling

- Fork failures are reported with `perror`.
- Failed `execve` calls are reported with `perror`, using the shell's
  program name, and the child exits with status `127`.
- Unknown commands print `<prog>: <line>: <command>: not found` to
  `stderr` and set the exit status to `127`.

## Limitations / Known issues

- No support for command-line arguments to built-ins (e.g. `exit 2`
  to set a custom exit status).
- No support for chaining (`;`, `&&`, `||`), piping (`|`), or I/O
  redirection (`>`, `<`).
- No support for comments (`#`).
- No environment-modifying built-ins (`setenv`, `unsetenv`, `cd`).
- Command line length is currently capped at 1023 tokens.

## Testing

Manual testing was performed by comparing this shell's output and
error output against `/bin/sh` for the same inputs, in both
interactive and non-interactive (piped) modes.

## Authors
Saud Sultan Alhaqbani
Saad Abdullah bin saeedan 
