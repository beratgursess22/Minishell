

#ifndef LEXER_H
#define LEXER_H



#include <stdio.h>
#include "../utils/libft/libft.h"
#include "../library/utils.h"


typedef enum s_token_type
{
    TOKEN_WORD, 	// 0
	TOKEN_PIPE, 	// 1
	TOKEN_INPUT, 	// 2
	TOKEN_OUTPUT, 	// 3
	TOKEN_APPEND, 	// 4
	TOKEN_HEREDOC 	// 5

} t_token_type;


typedef struct s_lexer
{
    char *word;
    t_token_type type;
    struct s_lexer *next;
    struct s_lexer *prev;
	int i;
    
} t_lexer;

// [TOKEN_WORD] "echo"  
// [TOKEN_WORD] "hello"  
// [TOKEN_PIPE] "|"  
// [TOKEN_WORD] "grep"  
// [TOKEN_WORD] "hi"  
// [TOKEN_OUTPUT] ">"  
// [TOKEN_WORD] "out.txt"
// 	TOKEN_APPEND, >>
//  TOKEN_HEREDOC, << 
 
t_lexer	*lexer(char *line);
void	add_lexer(t_lexer **head, t_lexer *new);

t_lexer	*new_lexer(char *str, t_token_type token);
void print_lexer(t_lexer *lst);
int parse_line(char *line, t_lexer **head, int i, int start);
int getting_word(t_lexer **head, int i, int start, char *line);


#endif 