#include "../library/minishell.h"


void print_cmds(t_parser *cmd) //cmd kontrol için yazılmış fonk
{
	int i = 1;
	while (cmd)
	{
		printf("CMD %d: ", i++);
		print_args(cmd->args);
		cmd = cmd->next;
	}
}

void print_args(char **args) // argüman kontrol için yazılmış fonk
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


void add_word_to_parser_list(t_lexer **head, int *i, int start, char *line) // |<> dışındaki şeyleri alıyor, yeni lexer ekliyor.
{

	while (line[(*i)] && !ft_isspace(line[(*i)]) && !ft_strchr("|<>",
					line[(*i)]))
				(*i)++;
	add_new_lexer_to_list(head, create_new_lexer(ft_strndup(&line[start], (*i) - start),
				TOKEN_WORD));
}


void parse_quotes(char *line, t_lexer **head, int *i, int start) //"" ve '' içlerini bir arada alıp lexer'a ekliyor.
{
	char quote;
	quote = line[(*i)];
	(*i)++;
	while (line[(*i)] && line[(*i)] != quote)
		(*i)++;
	if (line[(*i)] == quote)
		(*i)++;
	if (line[(*i) - 1] != quote)
		exit(0); //error handling eklenicek
	add_new_lexer_to_list(head, create_new_lexer(ft_strndup(&line[start], (*i) - start),
				TOKEN_WORD));
}


t_parser *create_parser_node(t_lexer **lexer) //Yeni bir komut (parser node u) oluşturur ve argümanlarını işler.
{
    t_parser *cmd;
    int count;

    cmd = calloc(1, sizeof(t_parser));
    count = count_args(*lexer);
    cmd->args = malloc(sizeof(char *) * (count + 1));
    if (!cmd->args)
        return (NULL);
    fill_args_to_parser(cmd, lexer);
    return (cmd);
}

void fill_args_to_parser(t_parser *cmd, t_lexer **lexer) //Komutun argümanlarını ve yönlendirmelerini (redir) doldurur.
{
    int i;

    i = 0;
    while (*lexer && (*lexer)->type != TOKEN_PIPE)
		{
			if ((*lexer)->type == TOKEN_WORD)
				cmd->args[i++] = ft_strdup((*lexer)->word);
            else
                handle_redirection(cmd, *lexer);
            *lexer = (*lexer)->next;
        }
    cmd->args[i] = NULL;
}

void handle_redirection(t_parser *cmd, t_lexer *lexer) //Redirection (input/output/heredoc/append) parametrelerini ayıklar.
{
    if (lexer->type == TOKEN_INPUT)
        cmd->infile = ft_strdup(lexer->word);
    else if (lexer->type == TOKEN_OUTPUT)
        cmd->outfile = ft_strdup(lexer->word);
    else if (lexer->type == TOKEN_HEREDOC)
        cmd->here_doc = ft_strdup(lexer->word);
    else if (lexer->type == TOKEN_APPEND)
        cmd->append = ft_strdup(lexer->word);
}


t_parser *main_parse_function(t_lexer *lexer)
{
    t_parser *head = NULL;
    t_parser *current = NULL;

    while (lexer)
    {
        t_parser *cmd = create_parser_node(&lexer);
        if (!head)
            head = cmd;
        else
            current->next = cmd;
        current = cmd;
        if (lexer && lexer->type == TOKEN_PIPE)
            lexer = lexer->next;
    }
    return (head);
}

int count_args(t_lexer *lexer) //Pipe (|) karakterine kadar olan alanda kaç tane TOKEN_WORD bulunduğunu sayar.
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
