#include "../../minishell.h"

void    gives_pipe_to_the_next_child(int fd1[2], int fd2[2], int i)
{
    if (i % 2 == 0)
    {
        close(fd1[0]);
        close(fd1[0]);
        pipe(fd1);
    }
    else
    {
        close(fd2[0]);
        close(fd2[1]);
        pipe(fd2);
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

void    execute_pipe(t_cmd *cmd, char **env)
{
    int fd1[2];
    int fd2[2];
    int pid;
    int i;

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("pipe");
        exit(1);
    }
    i = 0;
    while (i < cmd->args_nbr)
    {
        pid = fork();
        if (pid == -1)
         perror("fork");
        else if (pid == 0)
        {
            setup_pipes(fd1, fd2, i, cmd);
            if (execve(cmd[i].args[0], cmd[i].args, env) == -1)
            {
                perror("execve");
                exit(1);
            }
            // found_cmd(cmd, env , i);
        }
        gives_pipe_to_the_next_child(fd1, fd2, i);
        i++;
    }
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    i = 0;
    while (i < cmd->args_nbr)
    {
        waitpid(pid, NULL, 0);
        i++;
    }
}