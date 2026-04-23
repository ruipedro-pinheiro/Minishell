*This project has been created as part of the 42 curriculum by Saouissi, Rpinheir*

# Description
**Minishell** is a 42 group project where the main goal is to build a simplified shell, in comparison with bash.
In global we must execute programs from PATH variable, code ourselves built-ins programs like cd, echo or env.
Within the scope, we manage pipes, redirections, Posix signals like SIGINT (CTRL+C), build history based on recent inputs.
There is also a environment cloning where we must manage environment variables, and so also using '$?' to get the exit status of the most recent execution and be able to expand variables with character '$'.

There is also a less visible task is to build, how we manage the prompt (the user inputs).
The manner we've decided to do is the following:
Input -> readline() -> lexer -> tokens -> parser -> struct with linked lists -> execution.
Technical details will be listed later.

# Instructions
To build the project:
```bash
make
```
To run it you can either:
```bash
make run
```
or
```bash
./minishell
```
### This will launch the program and will run until you close it (Ctr+D, exit, etc...)
Feel free to test with those examples:
```bash
ls -la
```
```bash
cat README.md | grep "Instructions"
```
```bash
infile "grep foo" "sort" "wc -l" outfile
```
```bash
here_doc EOF "cat" "wc -l" outfile
```

# Resources

### Minishell 42 Guides
- [42 Docs - Minishell](https://harm-smits.github.io/42docs/projects/minishell) -- community docs, each step detailed
- [Minishell: Building a mini-bash](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218) -- 42 student, lexer -> parser -> executor flow
- [Mastering Minishell](https://haglobah.github.io/Mastering-42/holy_graph/minishell.html) -- comprehensive guide

### Parsing/Lexer Theory
- [Intro to Parsing & Lexing](https://dev.to/elipie/intro-to-parsing-lexing-3g01) -- basics for beginners
- [Shell parsing tips](https://shell.multun.net/parser.html) -- shell parser in detail

### Videos
- [Bash Shell Operation In Depth](https://youtube.com/watch?v=GGNzB_o4OiM) -- how bash processes a command
- [Build a simple shell in C](https://youtube.com/watch?v=yTR00r8vBH8) -- shell from scratch

### Others:
- [Code crafters](https://app.codecrafters.io/courses/shell/overview) -- non 42 project that is also very close to what we have to do
