/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void execute_first_command_env(char **str, var_t *var, int *status)
{
    pid_t pid = 0;

    pipe(var->pipedes);
    pid = fork();
    if (!pid) {
        close(var->pipedes[0]);
        dup2(var->pipedes[1], STDOUT_FILENO);
        close(var->pipedes[1]);
        my_show_word_array(var->env);
        exit(EXIT_SUCCESS);
    }
    close(var->pipedes[1]);
}

void handle_pipe_env(char **str, var_t *var)
{
    char **commands = NULL;
    int status = 0;
    pid_t pid2 = 0;
    var->pipedes = malloc(sizeof(int) * 2);
    var->indice = get_indice_pipe(str);
    if (var->indice > 0) {
        check_ambiguous_input_redirection(str, var);
        if (!str[var->indice + 1] || !my_strcmp(str[var->indice + 1], "|")) {
            write(2, "Invalid null command.\n", 22); exit(EXIT_FAILURE);
        }
        str[var->indice] = NULL;
        execute_first_command_env(str, var, &status);
        commands = get_commands(var, str);
        pid2 = fork();
        execute_second_command(commands, var, pid2, &status);
        close(var->pipedes[0]); close(var->pipedes[1]);
        waitpid(pid2, &status, 0);
        handle_errors(status, var);
        exit(var->return_value);
    }
}
