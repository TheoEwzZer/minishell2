/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void redirection(char **str, var_t *var, bool redirect, bool overwrite)
{
    int oflag = 0;

    if (redirect) {
        if (overwrite)
            oflag = O_CREAT | O_WRONLY | O_TRUNC;
        else
            oflag = O_CREAT | O_WRONLY | O_APPEND;
        var->fd = open(str[var->indice + 1], oflag, 0644);
        var->saved_stdout = dup(STDOUT_FILENO);
        dup2(var->fd, STDOUT_FILENO);
    }
}

void env_redirection(char **str, var_t *var)
{
    bool redirect = false;
    bool overwrite = false;
    var->indice = get_indice(str);
    if (!my_strcmp(str[var->indice], ">")
    || !my_strcmp(str[var->indice], ">>")) {
        redirect = true;
        if (!my_strcmp(str[var->indice], ">"))
            overwrite = true;
        if (!str[var->indice + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            var->return_value = 1; exit(1);
        }
        if (access(str[var->indice + 1], F_OK) == 0
        && access(str[var->indice + 1], W_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": Permission denied.\n", 21);
            var->return_value = 1;
            exit(1);
        }
    } redirection(str, var, redirect, overwrite);
}

unsigned int get_indice(char **str)
{
    unsigned int indice = 0;
    for (unsigned int i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], ">") || !my_strcmp(str[i], ">>")) {
            indice = i;
            break;
        }
    }
    return indice;
}

void handle_redirection(char **str, var_t *var)
{
    bool redirect = false, overwrite = false;
    var->indice = get_indice(str);
    if (str[var->indice]
    && (!my_strcmp(str[var->indice], ">")
    || !my_strcmp(str[var->indice], ">>"))) {
        redirect = true;
        if (!my_strcmp(str[var->indice], ">"))
            overwrite = true;
        if (!str[var->indice + 1]) {
            write(2, "Missing name for redirect.\n", 27);
            var->return_value = 1; exit(1);
        }
        if (access(str[var->indice + 1], F_OK) == 0
        && access(str[var->indice + 1], W_OK) == -1) {
            write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
            write(2, ": Permission denied.\n", 21);
            var->return_value = 1; exit(1);
        }
        str[var->indice] = NULL;
    } redirection(str, var, redirect, overwrite);
}
