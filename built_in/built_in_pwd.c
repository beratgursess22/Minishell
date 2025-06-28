#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "../library/built_in.h"

int built_in_pwd(t_parser *parser)
{
    char cwd[1024];

   (void)parser;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_putendl_fd(cwd, 1);
    else
    {
        ft_putstr_fd("minishell: pwd: ", 2);
        perror("");
        return (1);
    }
    return (0);
}