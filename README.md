# Simple Shell

This project is a simple UNIX shell written in C.

The shell reads commands from the user and executes them.

It displays a prompt and waits for the user to enter a command.

It can execute commands with arguments.

It can find commands using the PATH environment variable.

It works in interactive and non-interactive mode.

It uses `fork` to create a new process.

It uses `execve` to execute commands.

It uses `wait` to wait for the child process.

To compile:


gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh


To run:

./hsh


Example:

- ls
- pwd
- echo Hello
- exit


Authors:

- Saud Sultan Alhaqbani
- Saad Abdullah Bin Saeedan

