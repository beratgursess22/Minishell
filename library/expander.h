
#ifndef EXPANDER_H
#define EXPANDER_H

typedef struct s_main_struct t_main_struct;

typedef struct t_enviroment s_enviroment;
typedef struct s_lexer t_lexer;



char *expand_string(const char *input, t_enviroment *env, int last_exit);//Tüm expansion kurallarını ($VAR, $?, '...', "...") çözen ana fonksiyon.
void expand_single_quote(const char **p, char **result); // '...' bloklarını literal olarak ekler.
void expand_double_quote(const char **p, char **result, t_enviroment *env, int last_exit); // "...$..." bloklarında $ expansion yapar.
void expand_variable(const char **p, char **result, t_enviroment *env, int last_exit); //$VAR veya $? expand eder.
void append_normal_char(const char **p, char **result); //Normal karakterleri result stringine ekler.
void expander(t_lexer *lexer, t_enviroment **envp, int exit_code);
char *ft_strjoin_free(char *s1, char *s2);
char *ft_strjoin_char(char *s, char c);

#endif