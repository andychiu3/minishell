## How to Use

To get started with the minishell project, follow these steps:

```
git clone <URL> minishell

cd minishell

make

./minishell
```

p.s. dependency: readline. Linux system should work fine but if you are using macOS will have to 

```
brew install readline
```
first and double check `Makefile` `RL_PATH` has the right path to readline

<br>

## Features

The minishell supports:

- Support both **interactive mode** and **Non-interactive mode** (`echo "echo hi" | ./minishell`)
  
- **Prompt history** is available with interactive mode

- Full support for `execve` to execute **external commands**.

- **Built-in commands**: `cd`, `echo`, `export`, `pwd`, `unset`, `env` and `exit`.  

- **Redirection operators**: `>` (overwrite), `<` (input), `>>` (append) and `<<` (heredoc).  

- **Piping** `|` for chaining commands.  

- **Signal handling** for interrupts (e.g., `Ctrl+C`, `Ctrl+D` and `Ctrl+\`).

- **Quotes**: `"` and `'`

Command parsing using an **Abstract Syntax Tree (AST)**.  

reference to bash 5.2.  

<br>

## Concepts and Skills

This project deepened understanding of key systems programming concepts and reinforced the following skills:  

- Process Management:

Utilized execve to handle command execution, managing processes and their environments effectively.

- Abstract Syntax Tree (AST)

Implemented a parser using AST to interpret and structure complex command inputs.

- Signal Handling:

Integrated signal management to handle user interrupts (e.g., Ctrl+C, Ctrl+\ and Ctrl+D).

- File Redirection and Piping:

Mastered implementation of >, <, >>, <<, and |.

- Built-in Commands:

Developed built-in functions like cd, echo, export and more.

<br>

## Testing

The project was tested with various online testers. 

Due to differences in test entry points please use testers that align with the project's input format for accurate results.
