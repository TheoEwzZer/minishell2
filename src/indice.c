/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

size_t get_indice_output(char **str)
{
    size_t indice = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], ">") || !my_strcmp(str[i], ">>")) {
            indice = i;
            break;
        }
    }
    return indice;
}

size_t get_indice_input(char **str)
{
    size_t indice = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], "<") || !my_strcmp(str[i], "<<")) {
            indice = i;
            break;
        }
    }
    return indice;
}

size_t get_indice_pipe(char **str)
{
    size_t indice = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], "|")) {
            indice = i;
            break;
        }
    }
    return indice;
}
