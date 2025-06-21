

#include "../library/utils.h"

int	ft_isspace(char line)
{
	if (line == ' ' || line == '\t' || line == '\n' || line == '\v'
		|| line == '\f' || line == '\r')
		return (1);
	return (0);
}


char *ft_strndup(const char *src, int len)
{
	char *dest = malloc(len + 1);
    int i;

	if (!dest)
		return NULL;
    i = 0;
	while (i < len)
    {
        dest[i] = src[i];
        i++;
    }
	dest[len] = '\0';
	return dest;
}