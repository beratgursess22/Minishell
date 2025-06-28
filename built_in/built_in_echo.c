

#include "../library/built_in.h"



int echo_help_for_n(char *str) // -n için yazılmış bir fonksiyonudur.
{
    int i;

    i = 1;
    if (!str || str[0] != '-' || str[1] != 'n')
        return (0);
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int built_in_echo(t_parser *parser) // echo taklit 
{
    int i;
    int n;

    i = 1;
    n = 1;
    if (parser->args[1] && echo_help_for_n(parser->args[1]))
    {
		n = 0;
		i++;
    }
    while (parser->args[i])
    {
        ft_putstr_fd(parser->args[i], 1);
        if (parser->args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (n)
        ft_putchar_fd('\n', 1);
    return (0);
}