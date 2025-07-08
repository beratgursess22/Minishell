


#include "../library/minishell.h"
#include "../library/enviroment.h"

void print_parser(t_parser *parser)
{
    printf("ARGS: ");
    for (int i = 0; parser->args && parser->args[i]; i++)
        printf("[%s] ", parser->args[i]);
    printf("\n");

    printf("infile: %s\n", parser->infile);
    printf("outfile: %s\n", parser->outfile);
    printf("append: %s\n", parser->append);
    printf("here_doc: %s\n", parser->here_doc);
}

void  redirect_input(const char *filemane) // < 
{
    int fd;
    fd = open(filemane, O_RDONLY);
    if (fd < 0)
    {
        perror(filemane);
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) < 0) // standart girdi klavye 
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}

void redirect_output(const char *filename) // >
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror(filename);
        exit(1);
    }
    if (dup2(fd , STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}


void redirect_output_append(const char *filename)
{
    int fd;
    
    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0)
    {
        perror(filename);
        exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}

void redirect_herodoc(const char *filename)
{
    int pipefd[2];
    char *line;
    size_t len;

    line = NULL;
    len = 0;
    
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
           break;
        if (ft_strcmp(line, filename) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);

    if (dup2(pipefd[0], STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(pipefd[0]);
        exit(1);
    }
    close(pipefd[0]);
}


void redirector(t_parser *parser)
{
    print_parser(parser);
    if (parser->infile)
        redirect_input(parser->infile);
    if (parser->outfile)
        redirect_output(parser->outfile);
    if (parser->append)
        redirect_output_append(parser->append);
    if (parser->here_doc)
        redirect_herodoc(parser->here_doc);
}

