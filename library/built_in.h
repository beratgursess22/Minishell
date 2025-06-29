#ifndef BUILT_H
#define BUILT_H

#include "../library/minishell.h"
#include "../library/enviroment.h"

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


#endif