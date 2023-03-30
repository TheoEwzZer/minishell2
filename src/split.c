/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** minishell
*/

#include "mysh.h"

void split2(char *input, size_t *i, size_t *j, char *new)
{
    if (input[*i] == '<' || input[*i] == '>') {
        new[(*j)++] = ' ';
        new[(*j)++] = input[(*i)++];
        if (input[*i] == '<' || input[*i] == '>')
            new[(*j)++] = input[(*i)++];
        new[(*j)++] = ' ';
        return;
    }
    if (input[*i] == '|') {
        if (*j > 0 && new[*j - 1] != ' ')
            new[*j++] = ' ';
        new[(*j)++] = input[(*i)++];
        new[(*j)++] = ' ';
        return;
    }
    new[(*j)++] = input[(*i)++];
}

char *split(char *input)
{
    char *new = malloc(strlen(input) * 2 + 1);
    size_t i = 0;
    size_t j = 0;

    if (input[0] == '<' || input[0] == '>' || input[0] == '|') {
        new[j++] = input[i++];
        new[j++] = ' ';
    }
    while (input[i])
        split2(input, &i, &j, new);
    new[j] = '\0';
    return new;
}
