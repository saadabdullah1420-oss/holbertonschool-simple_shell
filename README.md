# Simple Shell

A simple UNIX command-line interpreter written in **C**.

The shell reads commands from the user, executes them, and displays the prompt again after each command.

## Features

* Display a prompt and wait for user input.
* Execute commands with arguments.
* Search for commands using the `PATH` environment variable.
* Support **interactive** and **non-interactive** modes.
* Create child processes using `fork`.
* Execute programs using `execve`.
* Wait for child processes using `wait`.

## Compilation

Compile the project using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

This creates an executable named:

```text
hsh
```

## Usage

Start the shell with:

```bash
./hsh
```

You can then enter commands such as:

```bash
ls
pwd
echo Hello
exit
```

### Example

```text
$ ./hsh
$ ls
$ pwd
$ echo Hello
Hello
$ exit
```

## How It Works

The shell follows a simple process:

1. Display the prompt.
2. Read the command entered by the user.
3. Parse the command and its arguments.
4. Create a child process using `fork`.
5. Execute the command using `execve`.
6. Wait for the child process to finish using `wait`.
7. Display the prompt again.

## Authors

* **Saud Sultan Alhaqbani**
* **Saad Abdullah Bin Saeedan**


