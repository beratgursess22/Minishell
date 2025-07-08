#include "../library/minishell.h"
#include "../library/enviroment.h"
#include "../library/herodoc.h"


void open_pipe_and_fork(t_parser *parser, char **env)
{
    int pipe_count;
    int i;
    int j;
    int k;
    pid_t pid;
    char *path;
    t_parser *current;
    
    j = 0;
    i = 0;
    current = parser;
    pipe_count = count_cmd(parser) -1;
    
    int pipes[pipe_count][2];
    while (i < pipe_count)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (current)
    {
        pid = fork();
        if (pid == 0)
        {
            redirector(parser);
            if (i != 0)
                dup2(pipes[i - 1][0], 0);
            if (current->next)
                dup2(pipes[i][1], 1);
            while (j < pipe_count)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }
            path = find_path(current->args[0], env);
            if (!path)
            {
                ft_putstr_fd("Komut bulunamadı: ", 2);
				ft_putendl_fd(current->args[0], 2);
				exit(127);
            }
            execve(path, current->args, env);
            perror("execve");
            exit(127);
        }
        current = current->next;
        i++;
    }
    j = 0;
    while (j < pipe_count)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    k = 0;
    while (k < count_cmd(parser))
    {
        wait(NULL);
        k++;
    }
}

void execute(char **cmd, t_main_struct *main_struct, t_parser *parser)
{
    int cmd_count;
    pid_t pid;
    char *path;

    cmd_count = count_cmd(parser);
    if (cmd_count == 1)
    {
        if (parser->built_type >= 0 && parser->built_type <= 6 )// ⬅️ cd, export, unset, exit gibi komutlar shell durumunu değiştirdiği için ana processte çalışmalı bu yüzden burada yaptık
		{
            run_built_in(parser, main_struct); // fork açmadan çalıştır.
            return ;
        }
        pid = fork();
        if (pid == 0)
        {

            if (parser->built_type == -1)// -1 yaptım yani bu builtin değil; ama 0 ve 6 arasında ise builtin fonksiyonudur
            {        
                redirector(parser);       
                path = find_path(*cmd, main_struct->env);
                if (!path)
                {
                    ft_putstr_fd("Komut bulunamadı: ", 2);
                    ft_putendl_fd(cmd[0], 2);
                    exit(127);
                }
                execve(path, cmd, main_struct->env);
                perror("execve");
                exit(127);
            }
        }
        else
            waitpid(pid, NULL, 0);
    }
    else
        open_pipe_and_fork(parser, main_struct->env);
}
