#include "../library/minishell.h"


void free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char  *find_path(char *cmd, char **env)
{
    int i;
    char **argv;
    char *path_final;
    char *path_split;

    i = 0;
    if (cmd[0] == '/' || (cmd[0] == '/' && cmd[1] == '.'))
    {
        if (access (cmd, F_OK | X_OK) == 0)
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    while (*env && ft_strncmp(*env, "PATH", 4))
        env++;
    argv = ft_split(*env + 5, ':');
    while (argv[++i])
    {
        path_split = ft_strjoin(argv[i],"/");
        path_final = ft_strjoin(path_split, cmd);
        free(path_split);
        if (access(path_final, F_OK | X_OK) == 0)
        {
            free_tab(argv);
            return (path_final);
        }
        free(path_final);
    }
    free_tab(argv);
    return (NULL);
}

int count_cmd(t_parser *parser)
{
    int i;

    i = 0;
    while (parser)
    {
        if (parser->args != NULL)
            i++;
        parser = parser->next;
    }
    return (i);
}



