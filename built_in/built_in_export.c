

#include "../library/built_in.h"


int print_export_list(t_enviroment *env_list)
{
    while (env_list)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(env_list->key, 1);
        if (env_list->value)
        {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(env_list->value, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putchar_fd('\n', 1);
        env_list = env_list->next;
    }
    return(0);
}



int built_in_export(t_parser *parser, t_enviroment **env)// tek export varsa list şeklinde terminale yazıyor ama ekleme yapmakta sıkınıtıs var. 
{
    int     i;
    char *value;
    char *value_orj;
    char *key;
    char *key_orj;
    
    i = 1;
    if (!parser->args[1])
        return(print_export_list(*env));
    while (parser->args[i])
    {
        value = parser->args[i];
        value_orj = ft_strchr(parser->args[i], '=');
        if (!value_orj)
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(parser->args[i], 2);
            ft_putendl_fd("': not a valid assignment", 2);
            i++;
        }
        key = ft_strndup(parser->args[i], (value_orj - value));
        key_orj = ft_strdup(value_orj + 1);

        if (get_env_value(key, *env))
            update_env_value(key, key_orj, env);
        else
            add_new_node_for_env(env, create_new_node_for_env(key, key_orj));
        free(key);
        free(key_orj);
        i++;
    }
    return(0);
}
