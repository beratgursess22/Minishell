#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../utils/libft/libft.h"
#include "../library/parser.h"
#include "../library/utils.h"
#include <string.h>
#include <unistd.h>
#include "../library/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	t_enviroment **env;
	t_main_struct *main_struct;
	char	*line;
	pid_t pid;

	init_env(envp, env);
	main_struct->env = envp;
	main_struct->env_struct = env;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line | !*line) 
		{
			printf("exit\n");
			free(line);
			exit(0);
		}
		if (line[0] != '\0') 
			add_history(line);
		t_lexer **tokens = lexer(line);
		// print_lexer(*tokens);
		t_parser *parsed = main_parse_function(*tokens);
		add_built_in_token(&parsed);
		// print_cmds(parsed);
		execute(parsed->args, main_struct, parsed);
		free(line);
	}
}


