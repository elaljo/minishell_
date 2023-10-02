#include "../minishell.h"

void    perror_pipe(void)
{
    perror("pipe");
    exit (1);
}
void    perror_fork(void)
{
    perror("fork");
    exit (1);
}
void    perror_fd(void)
{
    perror("fd");
    exit (1);
}