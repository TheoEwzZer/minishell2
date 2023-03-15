/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void redirection_input(char **str, var_t *var, bool overwrite)
{
    int oflag = O_CREAT | O_WRONLY;
    oflag = overwrite ? oflag | O_TRUNC : oflag | O_APPEND;
    if (str[var->indice] && !my_strcmp(str[var->indice], "<")) {
        if ((var->fd = open(str[var->indice + 1], O_RDONLY)) == -1) {
            var->return_value = 1;
            return;
        }
        dup2(var->fd, STDIN_FILENO);
    } else {
        if ((var->fd = open(str[var->indice + 1], oflag, 0644)) == -1) {
            var->return_value = 1;
            return;
        }
        dup2(var->fd, STDOUT_FILENO);
    }
    close(var->fd);
}

void redirection_outpout(char **str, var_t *var)
{
    if ((var->fd = open(str[var->indice + 1], O_RDONLY)) == -1) {
        var->return_value = 1;
        exit(1);
    }
    dup2(var->fd, STDIN_FILENO);
    close(var->fd);
}

void env_redirection(char **str, var_t *var)
{
    bool overwrite = false;
    var->indice = get_indice_outpout(str);
    if (!my_strcmp(str[var->indice], ">")
    || !my_strcmp(str[var->indice], ">>")) {
        if (!my_strcmp(str[var->indice], ">"))
            overwrite = true;
        if (!str[var->indice + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            var->return_value = 1; exit(1);
        }
        if (!access(str[var->indice + 1], F_OK)
        && access(str[var->indice + 1], W_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": Permission denied.\n", 21);
            var->return_value = 1;
            exit(1);
        }
    } redirection_input(str, var, overwrite);
}

void handle_outpout_redirection(char **str, var_t *var)
{
    bool overwrite = false;
    var->indice = get_indice_outpout(str);
    if (var->indice > 0) {
        check_error_outpout_redirection(str, var, &overwrite);
        redirection_input(str, var, overwrite);
    }
}

void handle_input_redirection(char **str, var_t *var)
{
    var->indice = get_indice_input(str);
    if (var->indice > 0) {
        if (!str[var->indice + 1]) {
            write(2, "Missing name for redirection.\n", 30);
            var->return_value = 1; exit(1);
        }
        if (access(str[var->indice + 1], F_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": No such file or directory.\n", 29);
            var->return_value = 1; exit(1);
        }
        if (!access(str[var->indice + 1], F_OK)
            && access(str[var->indice + 1], W_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": Permission denied.\n", 21);
            var->return_value = 1; exit(1);
        }
        str[var->indice] = NULL;
        redirection_outpout(str, var);
    }
}
