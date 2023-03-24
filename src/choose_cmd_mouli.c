/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void choose_cmd_mouli2(char **str, var_t *var)
{
    if (!my_strcmp(str[0], "setenv")) {
        builtin_setenv(str, var);
        return;
    }
    if (!my_strcmp(str[0], ">") || !my_strcmp(str[0], ">>")
    || !my_strcmp(str[0], "<") || !my_strcmp(str[0], "<<"))
        begin_with_redirection(str, var);
    check_not_found_and_close(str, var);
}

void choose_cmd_mouli(char **str, var_t *var)
{
    if (!my_strcmp(str[0], "cd")) {
        builtin_cd(str, var);
        return;
    }
    if (!my_strcmp(str[0], "exit")) {
        builtin_exit(str, var);
        return;
    }
    if (!my_strcmp(str[0], "unsetenv")) {
        builtin_unsetenv(str, var);
        return;
    }
    if (!my_strcmp(str[0], "env")
    || (!my_strcmp(str[0], "setenv")
    && (!str[1] || !my_char_isnum(str[1][0])))) {
        str[0] = my_strdup("env");
        builtin_env(str, var);
        return;
    }
    choose_cmd_mouli2(str, var);
}
