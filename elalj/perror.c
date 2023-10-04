#include "../minishell.h"

void    perror_pipe(void)
{
    perror("pipe");
    g_exit_status.status = 1;
    exit (1);
}
void    perror_fork(void)
{
    perror("fork");
    g_exit_status.status = 1;
    exit (1);
}
void    perror_fd(void)
{
    perror("fd");
    g_exit_status.status = 1;
    exit (1);
}
void    perror_execve(void)
{
    perror("execve");
    g_exit_status.status = 1;
    exit (1);
}