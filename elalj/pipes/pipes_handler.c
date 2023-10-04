#include "../../minishell.h"

void    execute_pipe(t_cmd *cmd, t_data *data)
{
    int fd1[2];
    int fd2[2];
    int i;
    
    if (pipe(fd1) == -1 || pipe(fd2) == -1)
        perror_pipe();
    start_executing_pipe(cmd, data, fd1, fd2);
    close_pipes(fd1, fd2);
    i = 0;
    while (i < cmd->args_nbr)
    {
        wait(&g_exit_status);
        i++;
    }
}

void    start_executing_pipe(t_cmd *cmd, t_data *data, int fd1[2], int fd2[2])
{
    int i;
    int pid_f;

    i = 0;
    while (i < cmd->args_nbr)
    {
        pid_f = fork();
        if (pid_f == -1)
            perror_fork();
        if (pid_f == 0)
        {
            setup_pipes(fd1, fd2, i, cmd);
            found_cmd(cmd, i, data);
        }
        gives_pipe_to_the_next_child(fd1, fd2, i);
        i++;
    }
}

void    setup_pipes(int fd1[2], int fd2[2], int i, t_cmd *cmd)
{
	if (i == 0)
		first_cmd(fd1, fd2);
	else if ((i == cmd->args_nbr - 1) && (i % 2 != 0))
		last_unpair(fd1, fd2);
	else if((i == cmd->args_nbr - 1) && (i % 2 == 0))
		last_pair(fd1, fd2);
	else if (i % 2 != 0)
		unpair(fd1, fd2);
	else if (i % 2 == 0)
		pair(fd1, fd2);
}


void    gives_pipe_to_the_next_child(int fd1[2], int fd2[2], int i)
{
    if (i % 2)
    {
        close(fd1[0]);
        close(fd1[1]);
        pipe(fd1);
    }
    else
    {
        close(fd2[0]);
        close(fd2[1]);
        pipe(fd2);
    }
}

void    close_pipes(int fd1[2], int fd2[2])
{
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
}
