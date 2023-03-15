/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void handle_errors(int status, var_t *var)
{
    int error = WTERMSIG(status);
    if (error && status != 136)
        write(2, strsignal(error), my_strlen(strsignal(error)));
    if (error && status == 136)
        write(2, "Floating exception", 18);
    if (WCOREDUMP(status)) {
        write(2, " (core dumped)\n", 15);
        var->return_value = status;
        return;
    }
    if (error) {
        write(2, "\n", 1);
        var->return_value = status;
        return;
    }
    if (WEXITSTATUS(status)) {
        var->return_value = WEXITSTATUS(status);
        return;
    }
    var->return_value = 0;
}

int handle_errors_setenv(char **str, var_t *var)
{
    unsigned int len = my_strlen_double(str);
    if (len > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        var->return_value = 1; return 84;
    } if (len == 1) {
        my_show_word_array(var->env);
        var->return_value = 0; return 84;
    } if (!my_char_isalpha(str[1][0])) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        var->return_value = 1; return 84;
    } if (!isalphanum(var->input)) {
        write(
            2,
            "setenv: Variable name must contain alphanumeric characters.\n",
            60
        );
        var->return_value = 1; return 84;
    }
    return 0;
}

void handle_errors_cd(char **str)
{
    struct stat st;
    if (str[2]) {
        write(2, "cd: Too many arguments.\n", 24);
        exit(1);
    }
    if (stat(str[1], &st) && my_strcmp(str[1], "-")) {
        write(2, str[1], my_strlen(str[1]));
        write(2, ": No such file or directory.\n", 29);
        exit(1);
    }
    if (!S_ISDIR(st.st_mode) && my_strcmp(str[1], "-")) {
        write(2, str[1], my_strlen(str[1]));
        write(2, ": Not a directory.\n", 19);
        exit(1);
    }
    if (access(str[1], X_OK) && my_strcmp(str[1], "-")) {
        write(2, str[1], my_strlen(str[1]));
        write(2, ": Permission denied.\n", 21);
        exit(1);
    }
}

void begin_with_redirection(char **str, var_t *var)
{
    char *tmp = NULL;
    if (!str[2] && !var->pid) {
        write(2, "Invalid null command.\n", 22);
        var->return_value = 1;
        exit(1);
    }
    tmp = str[2];
    for (unsigned int i = 2; i > 0; i--) {
        str[i] = str[i - 1];
    }
    str[0] = tmp;
}

void check_error_output_redirection(char **str, var_t *var, bool *overwrite)
{
    struct stat st;
    *overwrite = my_strcmp(str[var->indice], ">") ? false : true;
    if (!str[var->indice + 1]) {
        write(2, "Missing name for redirect.\n", 27);
        var->return_value = 1; exit(1);
    }
    stat(str[var->indice + 1], &st);
    if (!access(str[var->indice + 1], F_OK) && S_ISDIR(st.st_mode)) {
        write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
        write(2, ": Is a directory.\n", 18);
        var->return_value = 1; exit(1);
    }
    if (!access(str[var->indice + 1], F_OK)
    && access(str[var->indice + 1], W_OK) == -1) {
        write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
        write(2, ": Permission denied.\n", 21);
        var->return_value = 1; exit(1);
    }
    str[var->indice] = NULL;
}
