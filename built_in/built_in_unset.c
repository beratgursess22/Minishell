

#include "../library/built_in.h"

int	built_in_unset(t_parser *parser, t_enviroment **env) // unset silme fonkisyonu link liste silme 
{
	int i;
	t_enviroment *tmp = *env;
	t_enviroment *prev = NULL;

	if (!parser->args[1])
		return (0);

	i = 1;
	while (parser->args[i])
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, parser->args[i]) == 0)
			{
				if (prev == NULL)
					*env = tmp->next;
				else
					prev->next = tmp->next;

				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}