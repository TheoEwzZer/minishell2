/*
** EPITECH PROJECT, 2022
** my_strncat.c
** File description:
** Concatenates n characters of the src string to the end of the dest string.
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, size_t size)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    for (int i = 0; i <= len_src && i < size; i++) {
        dest[len_dest + i] = src[i];
    }
    return dest;
}
