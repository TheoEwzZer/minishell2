/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void begin_with_pipe(char **str, var_t *var)
{
    if (!my_strcmp(str[0], "|")) {
        if (!var->pid) {
            write(2, "Invalid null command.\n", 22);
            var->return_value = 1;
            exit(1);
        }
    }
}
