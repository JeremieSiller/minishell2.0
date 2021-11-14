# 42cursus03-Minishell

## Table of contents

1. [About](#about)
2. [How to use](#howtouse)
2. [libft](#libft)

## About

Minishell is a project of the 42-core-curriculum and the goal of this project is to write a simple shell. It is about learning the usage of filedescriptors, pipes
and about a deeper understanding about the bash.
It uses GNU's readline library which handles the terminal presentation (history, reading, ...)
The subject allows you only to use a few low-level functions (like malloc, free etc. ) and a few POSIX system calls.
It was a 2 person project with @nschumac who was responsible for parsing and signal handling. I was repsonsible for
the executing part and we both did some builtin commands.

## how to use

Clone the repository:
```bash
git clone --recursive https://github.com/ayeCaptainJack/minishell2.0/edit/master/README.md
```
run make to compile the programm:
```
make
```
execute the programm with out arguements to show a prompt and start the shell:
```bash
./minishell
```
or with a command as the first arguement
```
./minishell "cd .. && ls -la | cat | grep minishell"
```

- pipes with `|`
- operators and parenthesis with `&&`, `||`, `()`
- redirections with `<`, `<<`, `>`, `>>`
- expanding enviorment variables with `$`
- expanding the last processes exit status with $?
- interpretating with `'` `"`
- interpretation of `*` for the current working directory (e.g ls *)
- built in functions:
    - `echo` with or without `-n`           (e.g `echo -n hello "world"`)
    - `cd` with parameters                  (e.g `cd ../directory`)
    - `env`                                 (lists all environment variabels)
    - `exit` with parameters                (e.g `exit 42`)
    - `export` with or without parameters   (e.g `export TEST="test variable" `)
    - `unset`                               (e.g `unset TEST `)
    - `pwd`                                 (shows current directory)
    - `false` and `true`                    (e.g `false || true && ls`)

## libft

the project uses the submodule libft which is an earlier project of the 42 core curriculum.
This libft was written by @nschumac and you can find it here: https://github.com/nschumac/42cursus00-Libft
