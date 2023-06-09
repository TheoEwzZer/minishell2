/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

char **create_str(var_t *var)
{
    char **str = NULL;

    if (var->input[my_strlen(var->input) - 1] != '\n') {
        char *big = malloc(sizeof(char) * (my_strlen(var->input) + 1));
        for (size_t i = 0; i < my_strlen(var->input) + 1; i++)
            big[i] = '\0';
        big = my_strcat(big, var->input);
        big = my_strcat(big, "\n");
        str = my_str_to_word_array(big);
    } else {
        str = my_str_to_word_array(var->input);
    }
    return str;
}

void get_input(var_t *var)
{
    char *saveptr1 = NULL;
    char *str_token = NULL;
    size_t len = 0;

    var->input = NULL;
    while (getline(&var->input, &len, stdin) != -1) {
        str_token = strtok_r(var->input, ";", &saveptr1);
        while (str_token) {
            var->input = split(str_token);
            cmd_mouli(var);
            str_token = strtok_r(NULL, ";", &saveptr1);
            var->input = NULL;
        }
        var->input = NULL;
    }
}
