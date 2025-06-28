

#ifndef ENV_H
#define ENV_H



typedef struct s_enviroment
{
    char *key;
    char *value;
    struct s_enviroment *next;

} t_enviroment;


t_enviroment *create_new_node_for_env(char *key, char *value);
void add_new_node_for_env(t_enviroment **head, t_enviroment *env);

#endif