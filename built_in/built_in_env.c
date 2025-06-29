



#include "../library/built_in.h"


int built_in_env(t_enviroment *env_list)
{
   while (env_list)
   {
        printf("%s=%s\n", env_list->key, env_list->value);
        env_list = env_list->next;
   }
   return(0);
}