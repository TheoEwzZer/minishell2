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

```text
∼/B-PSU-210> ./mysh
> ls -l; ls -l | wc -l
total 4
drwxr-xr-x 2 johan johan 4096 Mar 17 16:28 tata
-rw-r–r– 1 johan johan 0 Mar 17 16:28 toto
3
>
```

```text
∼/B-PSU-210> ./mysh
> mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu
. ..
5
>
```
