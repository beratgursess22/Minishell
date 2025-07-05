


#include "../library/minishell.h"
#include "../library/enviroment.h"


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
    if (dup2(fd , STDOUT_FILENO)< 0)
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

}