#include "../library/parser.h"


int getting_word(t_lexer **head, int i, int start, char *line) // |<> dışındaki şeyleri alıyor, yeni lexer ekliyor.
{
	while (line[i] && !ft_isspace(line[i]) && !ft_strchr("|<>",
					line[i]))
				i++;
	add_lexer(head, new_lexer(ft_strndup(&line[start], i - start),
				TOKEN_WORD));
	return (i);
}


int parse_line(char *line, t_lexer **head, int i, int start) //"" ve '' içlerini bir arada alıp lexer'a ekliyor.
{
	char quote;
	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	if (line[i - 1] != quote)
		exit(0);
	add_lexer(head, new_lexer(ft_strndup(&line[start], i - start),
				TOKEN_WORD));
	return (i);
}

void print_args(char **args)
{
    if (!args || !args[0])
    {
        printf("Args: []\n");
        return;
    }

    printf("Args: [");
    for (int i = 0; args[i]; i++)
    {
        printf("\"%s\"", args[i]);
        if (args[i + 1])
            printf(", ");
    }
    printf("]\n");
}

void print_cmds(t_parser *cmd)
{
	int i = 1;
	while (cmd)
	{
		printf("CMD %d: ", i++);
		print_args(cmd->args);
		cmd = cmd->next;
	}
}


t_parser  *parse_arg(t_lexer *lexer) // lexer'dan argümanları alıp char ** olarak döndürüyor.
{
	t_parser *head = NULL;
	t_parser *current = NULL;
	t_parser *cmd;
	int count;
	int i;

	while (lexer)
	{
		cmd = calloc(1, sizeof(t_parser));
		count = count_args(lexer);
		cmd->args = malloc(sizeof(char *) * (count + 1));

		if (!cmd->args)
			return NULL;

		i = 0;
		while (lexer && lexer->type != TOKEN_PIPE)
		{
			if (lexer->type == TOKEN_WORD)
				cmd->args[i++] = ft_strdup(lexer->word);
			else if (lexer->type == TOKEN_INPUT)
				cmd->infile = ft_strdup(lexer->word);
			else if (lexer->type == TOKEN_OUTPUT)
				cmd->outfile = ft_strdup(lexer->word);
			else if (lexer->type == TOKEN_HEREDOC)
				cmd->here_doc = ft_strdup(lexer->word);
			else if (lexer->type == TOKEN_APPEND)
				cmd->append = ft_strdup(lexer->word);
			lexer = lexer->next;
		}
		cmd->args[i] = NULL;

		if (!head)
			head = cmd;
		else
			current->next = cmd;
		current = cmd;

		if (lexer && lexer->type == TOKEN_PIPE)
			lexer = lexer->next;
	}
	// print_cmds(head);
	return head;
}

int count_args(t_lexer *lexer)
{
	int count;
	if (!lexer)
		return 0;
	count = 0;
	while (lexer && lexer->type != TOKEN_PIPE)
	{
		if (lexer->type == TOKEN_WORD)
			count++;
		lexer = lexer->next;
	}
	return count;
}