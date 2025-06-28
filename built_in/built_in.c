#include "built_in.h"



void add_built_in_token(t_parser **head) // düzenlenicek.
{
	t_parser *new_parser;
	new_parser = *head;
	int i;
    char **built_in = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	while (new_parser)
	{
		i = 0;
		while (built_in[i])
		{
			if(ft_strcmp(new_parser->args[0], built_in[i]) == 0)
				new_parser->built_type = i;
				new_parser->lexer->type = TOKEN_BUILT_IN;
			i++;
		}
		new_parser = new_parser->next;
	}
}


int run_built_in(t_parser *parser) //hangi built_in olduğuna göre gerekli fonksiyonu çalıştırır.Built-in tokenlerine göre bakar
{
	if (parser->built_type == ECHO)
		return (built_in_echo(parser));
	else if (parser->built_type == CD)
		return (built_in_cd(parser));
	else if (parser->built_type == PWD)
		return (built_in_pwd(parser));
	else if (parser->built_type == EXPORT)
		return (built_in_export(parser));
	else if (parser->built_type == UNSET)
		return (built_in_unset(parser));
	else if (parser->built_type == ENV)
		return (built_in_env(parser));
	else if (parser->built_type == EXIT)
		return (built_in_exit(parser));
	return (-1);
}


int built_in_echo(t_parser *parser)
{
	

}

