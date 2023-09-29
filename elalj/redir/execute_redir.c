#include "../../minishell.h"

void    execute_redir(t_cmd *cmd, t_data *data)
{
    int pid_f;
    int fd;
    int i;

    pid_f = fork();
    if (pid_f == 0)
    {
        i = 0;
        while (cmd->redir_nbr != 0)
        {
            if (ft_strcmp(cmd[0].redir[i].redi, ">") == 0)
            {
                fd = open(cmd[0].redir[i].eof, O_RDWR | O_CREAT | O_TRUNC, 0644);
                dup2(fd, 1);
            }
            else if (ft_strcmp(cmd[0].redir[i].redi, "<") == 0)
            {
                if (access(cmd[0].redir[i].eof, F_OK) == 0)
                {
                    fd = open(cmd[0].redir[i].eof, O_RDONLY);
                    dup2(fd, 0);
                }
                else
                {
                    ft_putstr_fd("minishell: ", 2);
                    ft_putstr_fd(cmd[0].redir[i].eof, 2);
                    ft_putstr_fd(": No such file or directory\n", 2);
                    exit (1);
                    // exit_status = 1;
                }
            }
            cmd->redir_nbr--;
            i++;
        }
        found_cmd(cmd, 0 , data);
    }
    else
        wait(NULL); 
}