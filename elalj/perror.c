#include "../minishell.h"

void    perror_pipe(t_data *data)
{
    perror("pipe");
    data->new_st = 1;
    exit (1);
}
void    perror_fork(t_data *data)
{
    perror("fork");
    data->new_st = 1;
    exit (1);
}
void    perror_fd(t_data *data)
{
    perror("fd");
    data->new_st = 1;
    exit (1);
}
void    perror_execve(t_data *data)
{
    perror("execve");
    data->new_st = 1;
    exit (1);
}