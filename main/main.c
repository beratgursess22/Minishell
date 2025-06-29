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

void print_env_list(t_enviroment *env_list)
{
    while (env_list != NULL)
    {
        printf("KEY: %s | VALUE: %s\n", env_list->key, env_list->value);
        env_list = env_list->next;
    }
}


int	main(int argc, char **argv, char **envp)
{
	t_enviroment **env_list = malloc(sizeof(t_enviroment *));
	t_main_struct *main_struct = malloc(sizeof(t_main_struct));
	char	*line;
	pid_t pid;

	init_env(envp, env_list);
	// print_env_list(*env_list);
	main_struct->env = envp;
	main_struct->env_struct = env_list;
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
		//expander fonksiyon ilk expander mı, varsa genişletme yap, 
		t_parser *parsed = main_parse_function(*tokens);
		add_built_in_token(&parsed);
		// print_cmds(parsed);
		execute(parsed->args, main_struct, parsed);
		free(line);
	}
}


