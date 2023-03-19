/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void redirection_output(char **str, var_t *var, bool overwrite)
{
    int oflag = O_CREAT | O_WRONLY;

    oflag = overwrite ? oflag | O_TRUNC : oflag | O_APPEND;
    if ((var->fd = open(str[var->indice + 1], oflag, 0644)) == -1) {
        var->return_value = 1;
        return;
    }
    dup2(var->fd, STDOUT_FILENO);
    close(var->fd);
}

void redirection_input(char **str, var_t *var)
{
    unsigned int i = var->indice + 2;
    unsigned int j = var->indice;

    if ((var->fd = open(str[var->indice + 1], O_RDONLY)) == -1)
        exit(EXIT_FAILURE);
    dup2(var->fd, STDIN_FILENO);
    close(var->fd);
    if (str[var->indice + 2] && str[var->indice + 3]
    && str[var->indice + 4] && !my_strcmp(str[var->indice + 2], ">"))
        i = var->indice + 4;
    else
        i = var->indice + 2;
    for (; str[i]; i++) {
        str[j] = str[i];
        j++;
    }
    str[j] = NULL;
}

void env_redirection(char **str, var_t *var)
{
    bool overwrite = false;
    var->indice = get_indice_output(str);
    if (var->indice > 0) {
        check_ambiguous_output_redirection(str, var);
        if (!my_strcmp(str[var->indice], ">"))
            overwrite = true;
        if (!str[var->indice + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            exit(EXIT_FAILURE);
        }
        if (!access(str[var->indice + 1], F_OK)
        && access(str[var->indice + 1], W_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": Permission denied.\n", 21);
            exit(EXIT_FAILURE);
        }
    }
    redirection_output(str, var, overwrite);
}

void handle_output_redirection(char **str, var_t *var)
{
    bool overwrite = false;

    var->indice = get_indice_output(str);
    if (var->indice > 0) {
        check_ambiguous_output_redirection(str, var);
        check_error_output_redirection(str, var, &overwrite);
        redirection_output(str, var, overwrite);
    }
}

void handle_input_redirection(char **str, var_t *var)
{
    if (get_indice_pipe(str))
        return;
    var->indice = get_indice_input(str);
    if (var->indice > 0) {
        check_ambiguous_input_redirection(str, var);
        if (!str[var->indice + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            exit(EXIT_FAILURE);
        } if (access(str[var->indice + 1], F_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": No such file or directory.\n", 29);
            exit(EXIT_FAILURE);
        } if (!access(str[var->indice + 1], F_OK)
            && access(str[var->indice + 1], W_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": Permission denied.\n", 21);
            exit(EXIT_FAILURE);
        }
        redirection_input(str, var);
    }
}
