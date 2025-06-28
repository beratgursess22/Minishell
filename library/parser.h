#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../utils/libft/libft.h"
#include "utils.h"

typedef enum s_token_type
{
    TOKEN_WORD, 	// 0
	TOKEN_PIPE, 	// 1
	TOKEN_INPUT, 	// 2
	TOKEN_OUTPUT, 	// 3
	TOKEN_APPEND, 	// 4
	TOKEN_HEREDOC, 	// 5
	TOKEN_BUILT_IN  // 6

} t_token_type;

typedef enum s_built_in_type
{
	ECHO,   // 0
	CD,     // 1
	PWD,    // 2
	EXPORT, // 3
	UNSET,  // 4
	ENV,    // 5
	EXIT,   // 6
} t_built_in_type;

typedef struct s_lexer
{
    char *word;
    t_token_type type;
    struct s_lexer *next;
    struct s_lexer *prev;
	int i; 
} t_lexer;

typedef struct s_parser
{
	t_lexer *lexer;
	char **args;
	char *infile;
    char *outfile;
    char *append;
    char *here_doc;
	t_built_in_type built_type;
	struct s_parser *next;
	struct s_parser *prev;
} t_parser;


//----- lexer fonksiyonları ------

t_lexer *create_new_lexer(char *str, t_token_type token);
void add_new_lexer_to_list(t_lexer **head, t_lexer *new_lexer);
void lexer_tokenize_input_and_output(t_lexer **head, char *line, int *i);
void lexer_tokenize_pipe_heredoc_append(t_lexer **head, char *line, int *i);
t_lexer **lexer(char *line);


// ----- parser fonksiyonları -----


void add_word_to_parser_list(t_lexer **head, int *i, int start, char *line);
void parse_quotes(char *line, t_lexer **head, int *i, int start);
t_parser *create_parser_node(t_lexer **lexer);
void fill_args_to_parser(t_parser *cmd, t_lexer **lexer);
void handle_redirection(t_parser *cmd, t_lexer *lexer);
t_parser *main_parse_function(t_lexer *lexer);
int count_args(t_lexer *lexer);

//----- deneme fonk ------
void print_args(char **args);
void print_cmds(t_parser *cmd);
void	print_lexer(t_lexer *lst);

#endif