/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void builtin_env(char **str, var_t *var)
{
    int status = 0;
    size_t len_cmd = 0;

    if (!var->pid) {
        handle_pipe_env(str, var);
        status = execve(var->cmd, str, var->env);
        exit(EXIT_SUCCESS);
    }
    waitpid(var->pid, &status, 0);
    if (str[1]) {
        env_redirection(str, var);
        free(var->cmd);
        len_cmd = my_strlen(str[1]) + 6;
        var->cmd = malloc(sizeof(char) * my_strlen(str[1]) + 6);
        for (size_t i = 0; i < len_cmd; var->cmd[i] = '\0', i++);
        var->cmd = my_strcat(var->cmd, "/bin/");
        var->cmd = my_strcat(var->cmd, str[1]);
    }
    my_show_word_array(var->env);
    dup2(var->save_fd, STDOUT_FILENO);
}
