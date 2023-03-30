/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void begin_with_redirection(char **str, var_t *var)
{
    char *tmp = NULL;
    if (!str[2] && !var->pid) {
        write(2, "Invalid null command.\n", 22);
        exit(EXIT_FAILURE);
    }
    tmp = str[2];
    for (size_t i = 2; i > 0; i--)
        str[i] = str[i - 1];
    str[0] = tmp;
}

void check_error_output_redirection(char **str, var_t *var, bool *overwrite)
{
    struct stat st;
    *overwrite = my_strcmp(str[var->indice], ">") ? false : true;
    if (!str[var->indice + 1]) {
        write(2, "Missing name for redirect.\n", 27);
        exit(EXIT_FAILURE);
    }
    stat(str[var->indice + 1], &st);
    if (!access(str[var->indice + 1], F_OK) && S_ISDIR(st.st_mode)) {
        write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
        write(2, ": Is a directory.\n", 18);
        exit(EXIT_FAILURE);
    }
    if (!access(str[var->indice + 1], F_OK)
    && access(str[var->indice + 1], W_OK) == -1) {
        write(2, str[var->indice + 1], my_strlen(str[var->indice + 1]));
        write(2, ": Permission denied.\n", 21);
        exit(EXIT_FAILURE);
    }
    str[var->indice] = NULL;
}

void check_ambiguous_input_redirection(char **str, var_t *var)
{
    bool found = false;

    for (size_t i = var->indice + 1; str[i]; i++) {
        if (!my_strcmp(str[i], "<") || !my_strcmp(str[i], "<<")) {
            found = true;
            break;
        }
    }
    if (found) {
        write(2, "Ambiguous input redirect.\n", 26);
        exit(EXIT_FAILURE);
    }
}

void check_ambiguous_output_redirection(char **str, var_t *var)
{
    bool found = false;

    for (size_t i = var->indice + 1; str[i]; i++) {
        if (!my_strcmp(str[i], ">") || !my_strcmp(str[i], ">>")) {
            found = true;
            break;
        }
    }
    if (found) {
        write(2, "Ambiguous output redirect.\n", 27);
        exit(EXIT_FAILURE);
    }
}
