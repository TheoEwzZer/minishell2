# minishell2

```
binary name : mysh
language : C
compilation : via Makefile, including re, clean and fclean rules
```
- The totality of your source files, except all useless files (binary, temp files, obj
    files,...), must be included in your delivery.
- All the bonus files (including a potential specific Makefile) should be in a directory
    named _bonus_.
- Error messages have to be written on the error output, and the program should
    then exit with the 84 error code (0 if there is no error).

## Prerequisite

The _minishell1_ is needed to be able to validate any minishell2 skills.

## Goals

The goal of the project is to enrich your _minishell1_ project by adding semicolons (‘;’), pipes (‘|’), and the four
    redirections (‘>’, ‘<’, ‘»’, ‘«’) management.

The priority management is a key part of this project.

```
Error output, standard input and standard output redirections will be considered as
bonuses.
```

## Authorized Functions

- malloc, free, exit, opendir, readdir, closedir, getcwd, chdir
- fork, stat, lstat, fstat, open, close, getline, strtok, strtok_r
- read, write, execve, access, isatty, wait, waitpid
- wait3, wait4, signal, kill, getpid, strerror, perror, strsignal
- _pipe_ , _dup_ , _dup_

## Examples

### ∇ Terminal - + x

```
∼/B-PSU-210> ./mysh
> ls -l; ls -l | wc -l
total 4
drwxr-xr-x 2 johan johan 4096 Mar 17 16:28 tata
-rw-r–r– 1 johan johan 0 Mar 17 16:28 toto
3
>
```
### ∇ Terminal - + x

```
∼/B-PSU-210> ./mysh
> mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu
. ..
5
>
```
