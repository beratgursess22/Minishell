
#include "../library/parser.h"
#include "../library/minishell.h"

void expander(t_lexer *lexer, t_enviroment **envp, int exit_code) // burda Token wordlara bakıyorum ve expand_stringe atıyorum ordan gelen yeni veriyi 
//lexer->word a atıyorum eskisini freeliyorum devamını expande oku 
{
	char *expanded;
	while (lexer)
	{
		if (lexer->type == TOKEN_WORD)
		{
			expanded = expand_string(lexer->word, *envp, exit_code);
			free(lexer->word);
			lexer->word = expanded;
		}
		lexer = lexer->next;
	}
}