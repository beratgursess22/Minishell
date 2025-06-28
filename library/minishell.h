
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



void singal_take_promt(void);
void singal_handler(int singal);
void execute(char **cmd, char **env, t_parser *parser);
int count_cmd(t_parser *parser);
#endif