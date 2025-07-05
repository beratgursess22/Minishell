
#ifndef MINISHELL_H
#define MINISHELL_H

#include "parser.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "pipe.h"
#include <aio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "built_in.h"
#include "enviroment.h"
#include "../library/minishell.h"
#include "../library/enviroment.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expander.h"


typedef struct s_main_struct
{
	t_parser *parser_struct;
	t_enviroment **env_struct;
	char **env;

} t_main_struct;

void singal_take_promt(void);
void singal_handler(int singal);
void execute(char **cmd, t_main_struct *main_struct, t_parser *parser);
int count_cmd(t_parser *parser);

#endif