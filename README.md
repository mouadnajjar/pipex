# Pipex

Pipex is a project that replicates the behavior of a shell pipeline. It takes an input file, two commands, and an output file as arguments, mimicking the following shell command:

< infile cmd1 | cmd2 > outfile

## Features

- **Input/Output Redirection:** Reads from a file and writes to a file.
- **Piping:** Connects the output of the first command to the input of the second command.
- **Error Handling:** Provides error messages and exit codes similar to a standard shell.
- **Process Management:** Uses POSIX system calls such as `fork()`, `pipe()`, `dup2()`, `execve()`, and `waitpid()`.

## Installation

To compile the project, simply run:

```sh
make
This will:

Compile the source files.
Build the associated libft library.
Link everything together to produce the executable pipex.
Usage
The executable requires exactly four arguments:

./pipex infile "cmd1" "cmd2" outfile
For example:

./pipex infiles/basic.txt "cat -e" "grep something" outfiles/output.txt
This command emulates:

< infiles/basic.txt cat -e | grep something > outfiles/output.txt

Testing:

You can test Pipex by comparing its output with the output of a shell pipeline. For instance:

< infiles/basic.txt cat -e | grep something > outfiles/output_tester.txt
Then, compare outfiles/output.txt and outfiles/output_tester.txt to verify the behavior.

Clean Up :
To remove object files:
                                                         make clean
To remove the executable and the copied library file:
                                                         make fclean

Requirements :
Language: C
Compiler: cc
Library: libft (must be present in the repository root)
Norms: Code complies with 42 School Norms
License
This project is for educational purposes.

Author
Monajjar - monajjar@student.1337.ma

---
