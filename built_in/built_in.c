#include "../library/built_in.h"
#include "../library/minishell.h"




void add_built_in_token(t_parser **head) // düzenlenicek.
{
	t_parser *new_parser;
	new_parser = *head;
	int i;
    char *built_in[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL}; // onunda NULL var ki, döngüyü durdurmak için. 
	while (new_parser)
	{
		i = 0;
		new_parser->built_type = -1;
		while (built_in[i])
		{
			if(ft_strcmp(new_parser->args[0], built_in[i]) == 0)
			{
				new_parser->built_type = i;
				// new_parser->lexer->type = TOKEN_BUILT_IN; Bu neden var bilmiyorum ama seg yiyoruz olmadığında yemiyoruz. 
				// printf("DEBUG: found built-in: %s -> type=%d\n", built_in[i], i);
			}
			i++;
		}
		new_parser = new_parser->next;
	}
}


// int run_built_in(t_parser *parser) // hangi built_in olduğuna göre gerekli fonksiyonu çalıştırır.Built-in tokenlerine göre bakar
// {
// 	if (parser->built_type == ECHO)
// 		return (built_in_echo(parser));
// 	else if (parser->built_type == CD)
// 		return (built_in_cd(parser));
// 	else if (parser->built_type == PWD)
// 		return (built_in_pwd(parser));
// 	else if (parser->built_type == EXPORT)
// 		return (built_in_export(parser));
// 	else if (parser->built_type == UNSET)
// 		return (built_in_unset(parser));
// 	else if (parser->built_type == ENV)
// 		return (built_in_env(parser));
// 	else if (parser->built_type == EXIT)
// 		return (built_in_exit(parser));
// 	printf("DEBUG: no built-in matched, built_type=%d\n", parser->built_type);
// 	return (-1);
// }



int run_built_in(t_parser *parser)
{
    if (parser->built_type == ECHO)
    	return (built_in_echo(parser));
    else if (parser->built_type == CD)
    {
        printf("DEBUG: running built-in CD\n");
        // return (built_in_cd(parser)); yapılcak
    }
    else if (parser->built_type == PWD)
        return (built_in_pwd(parser));
    else if (parser->built_type == EXPORT)
    {
        printf("DEBUG: running built-in EXPORT\n");
        // return (built_in_export(parser)); yapılcak
    }
    else if (parser->built_type == UNSET)
    {
        printf("DEBUG: running built-in UNSET\n");
        // return (built_in_unset(parser)); yapılcak
    }
    else if (parser->built_type == ENV)
    {
        printf("DEBUG: running built-in ENV\n");
        // return (built_in_env(parser)); yapılcak
    }
    else if (parser->built_type == EXIT)
        return (built_in_exit(parser)); 

    printf("DEBUG: no built-in matched, built_type=%d\n", parser->built_type);
    return (-1);
}


