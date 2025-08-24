# Minishell #

- Minishell is one of the mandatory projects at 42. The goal is to recreate a simplified shell to understand how Unix shells work. 
Through this project we learned and implemented system calls such as fork, execve, pipe, dup2, readline, and signal, while also handling 
process management, memory management, and terminal control.

# Features # 

1- Prompt: Dynamic prompt using readline

2- Lexer & Parser: Tokenizes input and builds a command structure

3- Expander: Expands environment variables like $VAR, $?

4- Executor: Runs commands via fork + execve

5- Supports pipes (|)

6 -Supports redirections <, >, >>, << (heredoc)

# Built-in commands #

1- echo

2 -cd

3- pwd

4 -export

5 -unset

6- env

7- exit

# Signal handling # 

1- Handles Ctrl-C, Ctrl-D, Ctrl-\

# Environment variables : Managed with a linked list

# Error handling: Proper messages for invalid commands, redirection errors, etc.

# How It Works # 

1- Get user input → readline("minishell $ ")

2 -Lexer → Split input into tokens (ls -l | grep txt > out)

3- Parser → Build a command list based on pipes/redirections

4- Expander → Expand env variables ($PATH, $?, $USER)

5- Executor →

6- If built-in → run directly

7- Else → find path → fork + execve

8- Handle pipes/redirections with dup2

9- Parent process → Wait for children with waitpid

10- Return to prompt


# Installation #

git clone git@github.com:beratgursess22/Minishell.git

cd minishell

make

./minishell








