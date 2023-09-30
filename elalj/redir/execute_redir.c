#include "../../minishell.h"

void    redir_output(char *eof, int fd)
{
    fd = open(eof, O_RDWR | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);
}
void    redir_append(char *eof, int fd)
{
    fd = open(eof, O_RDWR | O_CREAT | O_APPEND, 0644);
    dup2(fd, 1);
}

void    redir_input(char *eof, int fd)
{
    if (access(eof, F_OK) == 0)
    {
        fd = open(eof, O_RDONLY);
        dup2(fd, 0);
    }
    else
    {
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(eof, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    exit (1);
    // exit_status = 1;
    }
}

void    execute_heredoc(char *eof)
{
    // create pipe
    // int pipe_fd[2];
    // int expand;
    // char *line;
    // char *expanded_line;

    if (ft_strcmp(eof, "\'") == 0 || ft_strcmp(eof, "\"") == 0) // check for single or double quote
        printf("ahh\n");
        // expand = 0;
    else
        printf("lae\n");
        // expand = 1;
    // pipe(pipe_fd);
    // while (1)
    // {
    //     line = get_next_line(0);
    //     if (strstr(line, del))
    //         break ;
    //     expanded_line = expand_all(line);
    //     if (expanded_line && expand)
    //         write(pipe_fd[1], expanded_line, strlen(expanded_line));
    //     else
    //         write(pipe_fd[1], line, strlen(line));
    //     free(line);
    // }
    // if (line)
    //     free(line);
    // dup2(pipe_fd[0], 0);
}

void    execute_redir(t_cmd *cmd, t_data *data)
{
    int pid_f;
    int fd;
    int i;

    fd = 0;
    pid_f = fork();
    if (pid_f == 0)
    {
        i = 0;
        while (cmd->redir_nbr != 0)
        {
            if (ft_strcmp(cmd[0].redir[i].redi, ">") == 0)
                redir_output(cmd[0].redir[i].eof, fd);
            else if (ft_strcmp(cmd[0].redir[i].redi, ">>") == 0)
                redir_append(cmd[0].redir[i].eof, fd);
            else if (ft_strcmp(cmd[0].redir[i].redi, "<") == 0)
                redir_input(cmd[0].redir[i].eof, fd);
            // else if (ft_strcmp(cmd[0].redir[i].redi, "<<") == 0)
            //     execute_heredoc(cmd[0].redir[i].eof);
            cmd->redir_nbr--;
            i++;
        }
        found_cmd(cmd, 0 , data);
    }
    else
        wait(NULL); 
}