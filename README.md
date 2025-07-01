# Minishell

A simplified UNIX shell written in C, developed as part of the 42 school curriculum.

## Project Goal

Recreate a functional shell that can interpret and execute user commands, handling parsing, environment variables, redirections, pipes, and built-in commands and closely mimicking real shell behavior.

## Features

- Prompt loop with input parsing
- Environment variable expansion
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Support for:
  - Pipes (`|`)
  - Redirections (`<`, `>`, `>>`, `<<`)
  - Quoting and escaping
  - Signal handling (`SIGINT`, `SIGQUIT`)
- Environment stored as a linked list
- Memory cleanup and error handling

## Build

```bash
make
```

## Usage

```bash
./minishell
```

Then type any valid shell command or built-in.

### Examples

```bash
ls -la | grep minishell
echo $HOME
export VAR=value
cat < file.txt > out.txt
```

---

## 📁 Project Structure

- `src/` – main shell logic (parsing, execution, builtins)
- `include/` – headers
- `libft/` – custom C library functions
- `Makefile` – build system

---

## Requirements

- Must behave like `bash` for basic inputs
- Must not use `system()` or any high-level shell wrappers
- Memory must be leak-free (verified with `valgrind`)
