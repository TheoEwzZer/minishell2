/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

bool check_command_not_found(char **str, var_t *var)
{
    if (str[0][0] != '/' && str[0][0] != '.' && !var->actu_path) {
        if (my_strcmp(str[0], "cd") &&
            my_strcmp(str[0], "exit") &&
            my_strcmp(str[0], "env") &&
            my_strcmp(str[0], "setenv") &&
            my_strcmp(str[0], "unsetenv")) {
                write(2, str[0], my_strlen(str[0]));
                write(2, ": Command not found.\n", 21);
                return true;
        }
    }
    return false;
}

void check_arg(int argc)
{
    if (argc != 1)
        exit(EXIT_FAILURE);
}
