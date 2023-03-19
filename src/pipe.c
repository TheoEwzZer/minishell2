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
    unsigned int j = 0;
    unsigned int num_args = 0;

    for (unsigned int i = var->indice + 1; commands[i]; i++)
        num_args++;
    new_commands = malloc(sizeof(char *) * (num_args + 1));
    for (unsigned int i = var->indice + 1; commands[i]; i++) {
        new_commands[j] = my_strdup(commands[i]);
        j++;
    }
    new_commands[j] = NULL;
    return new_commands;
}

void execute_first_command(char **str, var_t *var)
{
    pid_t pid = 0;

    pipe(var->pipedes);
    pid = fork();
    if (!pid) {
        close(var->pipedes[0]);
        dup2(var->pipedes[1], STDOUT_FILENO);
        close(var->pipedes[1]);
        if ((execve(var->cmd, str, var->env)) == -1) {
            try_path(str, var);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    close(var->pipedes[1]);
}

void execute_second_command(char **commands, var_t *var, pid_t pid2)
{
    if (!pid2) {
        close(var->pipedes[1]);
        dup2(var->pipedes[0], STDIN_FILENO);
        close(var->pipedes[0]);
        if ((execve(var->cmd, commands, var->env)) == -1) {
            try_path(commands, var);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}

bool handle_pipe(char **str, var_t *var)
{
    char **commands = NULL;
    int status = 0;
    pid_t pid2 = 0;
    var->pipedes = malloc(sizeof(int) * 2);
    var->indice = get_indice_pipe(str);
    if (var->indice > 0) {
        if (!str[var->indice + 1] || !my_strcmp(str[var->indice + 1], "|")) {
            write(2, "Invalid null command.\n", 22);
            exit(EXIT_FAILURE);
        }
        str[var->indice] = NULL;
        execute_first_command(str, var);
        commands = get_commands(var, str);
        pid2 = fork();
        execute_second_command(commands, var, pid2);
        close(var->pipedes[0]);
        close(var->pipedes[1]);
        waitpid(pid2, &status, 0);
        return true;
    } return false;
}
