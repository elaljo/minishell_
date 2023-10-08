#include "../minishell.h"

void    perror_pipe()
{
    perror("pipe");
    exit (1);
}
void    perror_fork()
{
    perror("fork");
    exit (1);
}
void    perror_fd()
{
    perror("fd");
    exit (1);
}
void    perror_execve()
{
    perror("execve");
    exit (1);
}