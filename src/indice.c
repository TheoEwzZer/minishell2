/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

unsigned int get_indice_output(char **str)
{
    unsigned int indice = 0;

    for (unsigned int i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], ">") || !my_strcmp(str[i], ">>")) {
            indice = i;
            break;
        }
    }
    return indice;
}

unsigned int get_indice_input(char **str)
{
    unsigned int indice = 0;

    for (unsigned int i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], "<") || !my_strcmp(str[i], "<<")) {
            indice = i;
            break;
        }
    }
    return indice;
}

unsigned int get_indice_pipe(char **str)
{
    unsigned int indice = 0;

    for (unsigned int i = 1; str[i]; i++) {
        if (!my_strcmp(str[i], "|")) {
            indice = i;
            break;
        }
    }
    return indice;
}
