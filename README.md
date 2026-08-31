# Simple Shell

## Description

This project is a simple UNIX command line interpreter written in C.

The shell reads commands from the user and executes them.

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

Run the shell:

```bash
./hsh
```

Example:

```text
($) ls
($) pwd
($) echo Hello
($) exit
```

The shell also works in non-interactive mode:

```bash
echo "/bin/ls" | ./hsh
```

## Authors

Saud Sultan Alhaqbani
Saad Abdullah Bin Saeedan

