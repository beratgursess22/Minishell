



#include "../library/built_in.h"
#include "../library/minishell.h"


int help_for_exit_numeric(const char *str)
{
    int i;

    i = 0;

    if (str[0] == '+' || str[0] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return(0);
        i++;
    }
    return(1);
}

int built_in_exit(t_parser *parser)
{
    int exit_code;

    ft_putendl_fd("exit", 1);

    if (!parser->args[1])
        exit(0);
    if (!help_for_exit_numeric(parser->args[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(parser->args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(255);
    }
    if (parser->args[2])
    {
        ft_putendl_fd("minishell: exit: : numeric argument required", 2);
        return (1);
    }
    exit_code  = (ft_atoi(parser->args[1]) % 256);
    return(exit_code);
}
