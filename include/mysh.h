/*
** EPITECH PROJECT, 2022
** mysh.h
** File description:
** mysh
*/

#ifndef MYSH_H_

    #define MYSH_H_

    #include "my.h"
    #include <errno.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>

typedef struct var {
    bool modify_env;
    bool redirect;
    char **env;
    char *actu_path;
    char *cmd;
    char *cwd;
    char *input;
    char *old_cwd;
    char *path;
    const char *home;
    int *pipedes;
    int fd;
    int return_value;
    int save_fd;
    pid_t pid;
    size_t indice;
} var_t;

bool check_command_not_found(char **str, var_t *var);
bool isalphanum(char *str);
char **create_str(var_t *var);
char **get_commands(var_t *var, char **commands);
char **my_strdup_double(char **src, char *env_to_set);
char **replace_cwd(char *new_cwd, var_t *var);
char *create_new_cwd(char *cwd);
char *create_new_env(char **str);
char *split(char *input);
int handle_errors_setenv(char **str, var_t *var);
int my_char_isalpha(char c);
int starts_with_digit_and_has_alnum(char *str);
size_t get_indice_input(char **str);
size_t get_indice_output(char **str);
size_t get_indice_pipe(char **str);
void begin_with_pipe(char **str, var_t *var);
void begin_with_redirection(char **str, var_t *var);
void builtin_cd(char **str, var_t *var);
void builtin_env(char **str, var_t *var);
void builtin_exit(char **str, var_t *var) __attribute__((noreturn));
void builtin_exit2(char **str, var_t *var) __attribute__((noreturn));
void builtin_setenv(char **str, var_t *var);
void builtin_unsetenv(char **str, var_t *var);
void change_cwd(char **str, var_t *var);
void check(char **str, var_t *var);
void check_ambiguous_input_redirection(char **str, var_t *var);
void check_ambiguous_output_redirection(char **str, var_t *var);
void check_arg(int argc);
void check_error_output_redirection(char **str, var_t *var, bool *overwrite);
void check_not_found_and_close(char **str, var_t *var);
void choose_cmd(char **str, var_t *var);
void choose_cmd_mouli(char **str, var_t *var);
void choose_cmd_mouli2(char **str, var_t *var);
void cmd_mouli(var_t *var);
void create_cmd(var_t *var, char **str);
void env_redirection(char **str, var_t *var);
void execute_first_command(char **str, var_t *var, int *status);
void execute_first_command_env(var_t *var);
void execute_second_command(char **commands, var_t *var, pid_t pid2, int *stat);
void found_home_and_path(var_t *var);
void free_env(var_t *var);
void free_var(var_t *var);
void get_input(var_t *var);
void handle_errors(int status, var_t *var);
void handle_errors_cd(char **str);
void handle_input_redirection(char **str, var_t *var);
void handle_output_redirection(char **str, var_t *var);
void handle_pipe(char **str, var_t *var);
void handle_pipe_env(char **str, var_t *var);
void parsing_path(var_t *var);
void redirection_input(char **str, var_t *var);
void redirection_output(char **str, var_t *var, bool overwrite);
void remove_env(char **str, size_t j, var_t *var);
void split2(char *input, size_t *i, size_t *j, char *new);
void try_path(char **str, var_t *var) __attribute__((noreturn));
void wait_cmd(char **env, var_t *var);
void wait_cmd2(size_t len_cmd, char **str, var_t *var);

#endif /* MYSH_H_ */
