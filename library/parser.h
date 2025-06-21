

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../utils/libft/libft.h"
#include "utils.h"



typedef struct s_parser
{
	t_lexer *lexer;
	char **args;
	char *infile;
    char *outfile;
    char *append;
    char *here_doc;
	struct s_parser *next;
	struct s_parser *prev;
} t_parser;

t_parser  *parse_arg(t_lexer *lexer);
int count_args(t_lexer *lexer);


int count_execute(t_parser *parser);


#endif