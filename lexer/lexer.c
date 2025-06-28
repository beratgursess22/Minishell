#include "../library/minishell.h"

void	print_lexer(t_lexer *lst) // deneme fonksiyonu, lexer'ın doğru çalışıp çalışmadığına bakmak için
{
	while (lst != NULL)
	{
		printf("%d .%s.\n",lst->type ,lst->word);
		lst = lst->next;
	}
}

t_lexer *create_new_lexer(char *str, t_token_type token) //sadece bir lexer node'u oluşturup tokeni ayarlar.
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->word = str;
	lexer->type = token;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

void add_new_lexer_to_list(t_lexer **head, t_lexer *new_lexer) //lexerlardan oluşan listenin sonuna yeni bir node ekler.
{
	t_lexer *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new_lexer;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_lexer;
	new_lexer->prev = tmp;
}

void lexer_tokenize_input_and_output(t_lexer **head, char *line, int *i) // input ve outputları tokenize eder ve lexer listesine ekler.
{
	if (line[*i] == '<')
	{
		add_new_lexer_to_list(head, create_new_lexer(ft_strdup("<"), TOKEN_INPUT));
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		add_new_lexer_to_list(head, create_new_lexer(ft_strdup(">"), TOKEN_OUTPUT));
		(*i)++;
	}
}

void lexer_tokenize_pipe_heredoc_append(t_lexer **head, char *line, int *i) // pipe, heredoc, appendleri tokenize eder ve lexer listesine ekler.
{
	if (line[(*i)] == '|')
	{
		add_new_lexer_to_list(head, create_new_lexer(ft_strdup("|"), TOKEN_PIPE));
		(*i)++;
	}
	else if (line[(*i)] == '<' && line[(*i) + 1] == '<')
	{
		add_new_lexer_to_list(head, create_new_lexer(ft_strdup("<<"), TOKEN_HEREDOC));
		(*i) += 2;
	}
	else if (line[(*i)] == '>' && line[(*i) + 1] == '>')
	{
		add_new_lexer_to_list(head, create_new_lexer(ft_strdup(">>"), TOKEN_APPEND));
		(*i) += 2;
	}
}



t_lexer **lexer(char *line) //lexer ile bir linked list yapısı oluşturur. Gelen tipe göre tokenize eder.
{
	t_lexer **head;
	int i;
	int start;

	start = 0;
	i = 0;
	head = malloc(sizeof(t_lexer *));
    *head = NULL;
	while(line[i])
	{
		while (ft_isspace(line[i]) == 1)
			i++;
		if ((ft_strchr("<", line[i]) && ft_strchr("<", line[i + 1])) || (ft_strchr(">", line[i]) && ft_strchr(">", line[i + 1])) || ft_strchr("|", line[i]))
			lexer_tokenize_pipe_heredoc_append(head, line, &i);
		else if (ft_strchr("|", line[i]) || ft_strchr("<", line[i]) || ft_strchr(">", line[i]))
			lexer_tokenize_input_and_output(head, line, &i);
		else
		{
			start = i;
			if (line[i] == '\"' || line[i] == '\'')
				parse_quotes(line, head, &i, start);
			else
				add_word_to_parser_list(head, &i, start, line);
		}
	}
	return (head);
}
// ayrıca bu fonksiyon bölünecek, sondaki else ayrı bir fonksiyona çekilicek.


