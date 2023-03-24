/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void check_not_found_and_close(char **str, var_t *var)
{
    int status = 0;

    begin_with_pipe(str, var);
    if (!var->pid) {
        handle_input_redirection(str, var);
        handle_output_redirection(str, var);
        handle_pipe(str, var);
        if ((status = execve(var->cmd, str, var->env)) == -1) {
            try_path(str, var);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(var->pid, &status, 0);
    handle_errors(status, var);
}

void create_cmd(var_t *var, char **str)
{
    unsigned int len_cmd = 0;

    if (var->actu_path)
        len_cmd = my_strlen(str[0]) + my_strlen(var->actu_path) + 2;
    else
        len_cmd = my_strlen(str[0]) + 2;
    var->cmd = malloc(sizeof(char) * len_cmd);
    for (unsigned int i = 0; i < len_cmd; var->cmd[i] = '\0', i++);
    if (str[0][0] != '.' && str[0][0] != '/') {
        if (var->actu_path)
            var->cmd = my_strcat(var->cmd, var->actu_path);
        var->cmd = my_strcat(var->cmd, "/");
    }
    var->cmd = my_strcat(var->cmd, str[0]);
}

void cmd_mouli(var_t *var)
{
    char **str = create_str(var);
    if (!str[0])
        return;
    if (check_command_not_found(str, var))
        return;
    var->cmd = NULL;
    if (my_strlen(var->input) <= 1) {
        var->return_value = 0;
        free(str);
        return;
    }
    if ((var->pid = fork()) == -1) {
        var->return_value = EXIT_FAILURE;
        free(str);
        return;
    }
    create_cmd(var, str);
    choose_cmd_mouli(str, var);
    free(var->cmd);
    free(str);
}

int main(int argc, char **argv, char **env)
{
    var_t *var = malloc(sizeof(var_t));

    check_arg(argc);
    var->return_value = 0;
    var->modify_env = false;
    var->env = env;
    var->old_cwd = my_strdup(getcwd(NULL, 0));
    var->actu_path = NULL;
    found_home_and_path(var);
    var->cwd = my_strdup(getcwd(NULL, 0));
    var->save_fd = dup(STDOUT_FILENO);
    if (!isatty(STDIN_FILENO)) {
        get_input(var);
    } else {
        while (42)
            wait_cmd(env, var);
    }
    return var->return_value;
}
