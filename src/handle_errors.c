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
        var->return_value = 1; return EXIT_FAILURE;
    } if (len == 1) {
        my_show_word_array(var->env);
        var->return_value = 0; return EXIT_FAILURE;
    } if (!my_char_isalpha(str[1][0])) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        var->return_value = 1; return EXIT_FAILURE;
    } if (!isalphanum(var->input)) {
        write(
            2,
            "setenv: Variable name must contain alphanumeric characters.\n",
            60
        );
        var->return_value = 1; return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void handle_errors_cd(char **str)
{
    struct stat st;
    if (str[2] && my_strcmp(str[2], "|")) {
        write(2, "cd: Too many arguments.\n", 24);
        exit(EXIT_FAILURE);
    }
    if (stat(str[1], &st) && my_strcmp(str[1], "-")) {
        write(2, str[1], my_strlen(str[1]));
        write(2, ": No such file or directory.\n", 29);
        exit(EXIT_FAILURE);
    }
    if (!S_ISDIR(st.st_mode) && my_strcmp(str[1], "-")) {
        write(2, str[1], my_strlen(str[1]));
        write(2, ": Not a directory.\n", 19);
        exit(EXIT_FAILURE);
    }
    if (access(str[1], X_OK) && my_strcmp(str[1], "-")) {
        write(2, str[1], my_strlen(str[1]));
        write(2, ": Permission denied.\n", 21);
        exit(EXIT_FAILURE);
    }
}
