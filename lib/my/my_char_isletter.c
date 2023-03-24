/*
** EPITECH PROJECT, 2023
** my_char_isletter.c
** File description:
** Returns 1 if the char passed as
** parameter is a letter and 0 otherwise.
*/

int my_char_isnum(char str)
{
    return (str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z');
}
