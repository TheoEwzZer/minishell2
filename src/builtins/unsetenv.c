/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void remove_env(char **str, size_t j, var_t *var)
{
    bool found = false;
    size_t len = my_strlen(str[j]);

    for (size_t i = 0; var->env[i]; i++) {
        if (!my_strncmp(var->env[i], str[j], len) && var->env[i][len] == '=')
            found = true;
        if (found)
            var->env[i] = var->env[i + 1] ? var->env[i + 1] : NULL;
    }
}

void builtin_unsetenv(char **str, var_t *var)
{
    int status = 0;

    if (!var->pid) {
        status = execve(var->cmd, str, var->env);
        exit(EXIT_SUCCESS);
    }
    waitpid(var->pid, &status, 0);
    handle_errors(status, var);
    if (!str[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        free_var(var);
        exit(EXIT_FAILURE);
    }
    for (size_t j = 1; str[j]; j++)
        remove_env(str, j, var);
}
