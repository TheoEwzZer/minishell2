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
        for (unsigned int i = 0; i < my_strlen(var->input) + 1; i++)
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
    char *saveptr1;
    size_t len = 0;

    var->input = NULL;
    while (getline(&var->input, &len, stdin) != -1) {
        char *strToken = strtok_r(var->input, ";", &saveptr1);
        while (strToken) {
            var->input = strToken;
            cmd_mouli(var);
            strToken = strtok_r(NULL, ";", &saveptr1);
            var->input = NULL;
        }
        var->input = NULL;
    }
}
