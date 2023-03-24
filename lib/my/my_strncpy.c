/*
** EPITECH PROJECT, 2022
** my_strncpy.c
** File description:
** Copies n characters from a string into another. The destination string
** will already have enough memory to contain n characters.
*/

#include "my.h"

char *my_strncpy(char *dest, char const *src, size_t size)
{
    int len = my_strlen(src);
    int i = 0;
    for (i ; i <= len && i < size; i++) {
        dest[i] = src[i];
    }
    return dest;
}
