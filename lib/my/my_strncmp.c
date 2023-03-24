/*
** EPITECH PROJECT, 2022
** my_strncmp.c
** File description:
** Reproduce the behavior of the strncmp function.
*/

#include "my.h"

int my_strncmp(char const *s1, char const *s2, size_t size)
{
    int i = 0;
    for (; s1[i] == s2[i] && i != size && s1[i] && s2[i]; i++) {
        continue;
    }
    if ((s1[i] == '\0' && s2[i] == '\0') || i == size) {
        return 0;
    }
    if (s1[i] > s2[i]) {
        return 1;
    }
    if (s1[i] < s2[i]) {
        return -1;
    }
    return 0;
}
