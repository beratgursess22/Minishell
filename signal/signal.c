
#include "../library/minishell.h"



void singal_handler(int singal)
{
    (void)singal;
    write(STDOUT_FILENO, "\n",1);
    //rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void singal_take_promt(void)
{
    signal(SIGINT, singal_handler);
    signal(SIGQUIT, SIG_IGN);
}


//buraya terminalde çalışma durumda Contorl C  ve Contorl \ gelecek 
//yani cat girdin terminal senden bir giriş bekler onu kesmek için yazman lazım 
// 