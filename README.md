# Minishell2

```text
binary name : mysh
language : C
compilation : via Makefile, including re, clean and fclean rules
```

## Prerequisite

The _minishell1_ is needed to be able to validate any minishell2 skills.

## Goals

The goal of the project is to enrich your _minishell1_ project by adding semicolons (‘;’), pipes (‘|’), and the four redirections (‘>’, ‘<’, ‘»’, ‘«’) management.

The priority management is a key part of this project.

```text
Error output, standard input and standard output redirections will be considered as bonuses.
```

## Authorized Functions

- malloc, free, exit, opendir, readdir, closedir, getcwd, chdir
- fork, stat, lstat, fstat, open, close, getline, strtok, strtok_r
- read, write, execve, access, isatty, wait, waitpid
- wait3, wait4, signal, kill, getpid, strerror, perror, strsignal
- _pipe_ , _dup_ , _dup2_

## Examples

```bash
∼/B-PSU-210> ./mysh
> ls -l; ls -l | wc -l
total 4
drwxr-xr-x 2 johan johan 4096 Mar 17 16:28 tata
-rw-r–r– 1 johan johan 0 Mar 17 16:28 toto
3
>
```

```bash
∼/B-PSU-210> ./mysh
> mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu
. ..
5
>
```

## FINAL MARK

### MARK: 45 / 49 (91.8%)

- Basic tests (5 / 5)
- Path handling (5 / 5)
- Setenv and unsetenv (2 / 2)
- Builtin cd (3 / 3)
- Line formatting (space and tabs) (8 / 8)
- Error handling (3 / 3)
- Separator (5 / 5)
- Simple pipe (4 / 4)
- Simple redirections (2 / 2)
- Advanced pipe (3 / 7)
- Advanced redirections (1 / 1)
- Advanced manipulations (4 / 4)
