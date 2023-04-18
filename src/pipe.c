/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void begin_with_pipe(char **str, var_t *var)
{
    if (str[0] && !my_strcmp(str[0], "|")) {
        if (!var->pid) {
            write(2, "Invalid null command.\n", 22);
            var->return_value = 1;
            exit(EXIT_FAILURE);
        }
    }
}

char **get_commands(var_t *var, char **commands)
{
    char **new_commands = NULL;
    size_t j = 0;
    size_t num_args = 0;

    for (size_t i = var->index + 1; commands[i]; i++)
        num_args++;
    new_commands = malloc(sizeof(char *) * (num_args + 1));
    for (size_t i = var->index + 1; commands[i]; i++) {
        new_commands[j] = my_strdup(commands[i]);
        j++;
    }
    new_commands[j] = NULL;
    return new_commands;
}

void execute_first_command(char **str, var_t *var, int *status)
{
    pid_t pid = 0;

    pipe(var->pipe_descriptor);
    pid = fork();
    if (!pid) {
        close(var->pipe_descriptor[0]);
        dup2(var->pipe_descriptor[1], STDOUT_FILENO);
        close(var->pipe_descriptor[1]);
        *status = execve(var->cmd, str, var->env);
        if (*status == -1) {
            try_path(str, var);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        close(var->pipe_descriptor[1]);
    }
}

void execute_second_command(char **commands, var_t *var, pid_t pid2, int *stat)
{
    if (!pid2) {
        create_cmd(var, commands);
        close(var->pipe_descriptor[1]);
        dup2(var->pipe_descriptor[0], STDIN_FILENO);
        close(var->pipe_descriptor[0]);
        if (!my_strcmp(commands[0], "cd")) {
            builtin_cd(commands, var);
            exit(EXIT_SUCCESS);
        }
        *stat = execve(var->cmd, commands, var->env);
        if (*stat == -1) {
            try_path(commands, var);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}

void handle_pipe(char **str, var_t *var)
{
    char **commands = NULL;
    int status = 0;
    pid_t pid = 0;
    var->pipe_descriptor = malloc(sizeof(int) * 2);
    var->index = get_index_pipe(str);
    if (var->index > 0) {
        check_ambiguous_input_redirection(str, var);
        if (!str[var->index + 1] || !my_strcmp(str[var->index + 1], "|")) {
            write(2, "Invalid null command.\n", 22); exit(EXIT_FAILURE);
        }
        str[var->index] = NULL;
        execute_first_command(str, var, &status);
        commands = get_commands(var, str);
        pid = fork();
        execute_second_command(commands, var, pid, &status);
        close(var->pipe_descriptor[0]); close(var->pipe_descriptor[1]);
        waitpid(pid, &status, WCONTINUED | WUNTRACED);
        handle_errors(status, var);
        exit(var->return_value);
    }
}
