/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

size_t get_index_output(char **str)
{
    size_t index = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], ">") || !my_strcmp(str[i], ">>")) {
            index = i;
            break;
        }
    }
    return index;
}

size_t get_index_input(char **str)
{
    size_t index = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], "<") || !my_strcmp(str[i], "<<")) {
            index = i;
            break;
        }
    }
    return index;
}

size_t get_index_pipe(char **str)
{
    size_t index = 0;

    for (size_t i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], "|")) {
            index = i;
            break;
        }
    }
    return index;
}
