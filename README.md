# 42cursus03-Minishell
## Description:
The goal of this project is to recreate [bash shell](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

### Features:
- interpretation of `|`, `&&`, `||`, `()`
- interpretation of `<`, `<<`, `>`, `>>`
- interpretation of `$`, `"`, `'`
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

## Usage:
**MacOs Linux only**
- `git clone --recursive https://github.com/nschumac/42cursus03-Minishell.git`
- install [readline library](https://tiswww.case.edu/php/chet/readline/rltop.html) (e.g `brew install readline`)
- run `make` in cloned repository
- execute `./minishell`

**you are now in a shell and can execute most commands (e.g ls -a | grep a | cat)**
## Subject:
<object data="https://github.com/nschumac/42cursus03-Minishell/blob/master/subject/minishell-en.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="https://github.com/nschumac/42cursus03-Minishell/blob/master/subject/minishell-en.pdf">
        <p><a href="https://github.com/nschumac/42cursus03-Minishell/blob/master/subject/minishell-en.pdf">minishell subject</a></p>
    </embed>
</object>

## Result:
- Status: <span style="color:green">Completed</span>
- Result: <span style="color:green">125%</span>

## Contact:
- 42-slack: nschumac
- 42-email: nschumac@student.42heilbronn.de
- 42-profile: [https://profile.intra.42.fr/users/nschumac](https://profile.intra.42.fr/users/nschumac)
