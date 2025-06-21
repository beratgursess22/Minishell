#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../utils/libft/libft.h"
#include "../library/lexer.h"
#include "../library/parser.h"
#include "../library/utils.h"
#include <string.h>
#include <unistd.h>
#include "../library/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>



int	main(int argc, char **argv, char **envp)
{
	char	*line;
	pid_t pid;
	singal_take_promt();

	while (1)
	{
		line = readline("minishell$ ");
		if (!line | !*line) 
		{
			printf("exit\n");
			free(line);
			exit(0);
		}
        if (strcmp(line , "exit") == 0)
        {
			free(line);
            break;
        }   
		if (line[0] != '\0') 
		add_history(line);
		t_lexer *argv = malloc(sizeof(char) * 1000);
		argv =  lexer(line);
		t_parser *head = parse_arg(argv);	
		execute(head->args, envp, head);
		free(line);
	}
	return (0);
}

