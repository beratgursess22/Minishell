
#include "../library/lexer.h"

void	print_lexer(t_lexer *lst)
{
	while (lst != NULL)
	{
		printf("%d .%s.\n",lst->type ,lst->word);
		lst = lst->next;
	}
}

t_lexer	*new_lexer(char *str, t_token_type token)//token oluşturcaz eksik 
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->word = str;
	lexer->type = token;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

void	add_lexer(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int lexer_helper_two(t_lexer **head, char *line, int i)
{
	if (line[i] == '<')
	{
		add_lexer(head, new_lexer(ft_strdup("<"), TOKEN_INPUT));
		i++;
	}
	else if (line[i] == '>')
	{
		add_lexer(head, new_lexer(ft_strdup(">"), TOKEN_OUTPUT));
		i++;
	}
	return (i);
}


int lexer_helper(t_lexer **head, char *line, int i)
{
	if (line[i] == '|')
	{
		add_lexer(head, new_lexer(ft_strdup("|"), TOKEN_PIPE));
		i++;
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		add_lexer(head, new_lexer(ft_strdup("<<"),	 TOKEN_HEREDOC));
		i += 2;
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		add_lexer(head, new_lexer(ft_strdup(">>"), TOKEN_APPEND));
		i += 2;
	}
	else if (line[i] == '<' || line[i] == '>')
		i = lexer_helper_two(head, line, i);
	return (i);
}


t_lexer	*lexer(char *line)
{
	t_lexer	*head;
	int		i;
    int	start;

    start = 0;
	i = 0;
	head = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]) == 1)
			i++;
		if (ft_strchr("|><", line[i]))
			i = lexer_helper(&head, line, i);
		else
		{
			start = i;
			if (line[i] == '\"' || line[i] == '\'')
			{
				i = parse_line(line, &head, i, start);
				continue;
			}
			i = getting_word(&head, i, start, line);
		}
	}
	// print_lexer(head);
	return (head);
}
