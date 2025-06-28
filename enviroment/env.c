

#include "../library/enviroment.h"
#include "../library/minishell.h"


t_enviroment *create_new_node_for_env(char *key, char *value) // enviroment için teni node açar
{
    t_enviroment *env;

    env = malloc(sizeof(t_enviroment));
    if (!env)
        return(NULL);
    env->key = key;
    env->value = value;
    env->next = NULL;
    return (env);
}

void add_new_node_for_env(t_enviroment **head, t_enviroment *env) // enviroment için list oluşturur 
{
    t_enviroment *temp;

    temp = *head;
    if (!temp)
    {
        *head = env;
        return ;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = env;
}

char *extract_key(char *str) //  sadece PATH ksımını almak için 
{
    int i;
    
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    return ft_strndup(str, i);
}

char *extract_value(char *str) // sadece usr/bin gibi değerleri almak için
{
    char *equal;

    equal = ft_strchr(str, '=');
    if (!equal)
        return ft_strdup("");
    return ft_strdup(equal + 1);
}


void init_copy_env

