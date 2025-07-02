
#include "../library/parser.h"
#include "../library/minishell.h"



char *ft_strjoin_char(char *s, char c)
{
    int len = ft_strlen(s);
    char *new_str = malloc(len + 2); // +1 char +1 null
    if (!new_str)
        return NULL;
    int i = 0;
    while (s && s[i])
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[i++] = c;
    new_str[i] = '\0';
    free(s);
    return new_str;
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *joined = ft_strjoin(s1, s2); // klasik ft_strjoin
    free(s1);
    free(s2);
    return joined;
}