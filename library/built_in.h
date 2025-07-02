#ifndef BUILT_H
#define BUILT_H

#include "../library/minishell.h"
#include "../library/enviroment.h"

typedef struct s_main_struct t_main_struct;

// ana fonksiyonlar 
int run_built_in(t_parser *parser, t_main_struct *main_struct);
void add_built_in_token(t_parser **head);

// built echo
int built_in_echo(t_parser *parser);
int echo_help_for_n (char *str);

// built exit
int help_for_exit_numeric(const char *str);
int built_in_exit(t_parser *parser);

// built pwd
int built_in_pwd(t_parser *parser);

//built cd
int built_in_cd(t_parser *parser, t_enviroment **env);

//build env
int built_in_env(t_enviroment *env_list);

//built export
int built_in_export(t_parser *parser, t_enviroment **env);
int print_export_list(t_enviroment *env_list);

// built_in_unset
int built_in_unset(t_parser *parser, t_enviroment **env);


//debug 
void print_env_list(t_enviroment *env_list);

#endif