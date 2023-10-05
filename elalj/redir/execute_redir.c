#include "../../minishell.h"

void    redir_output(char *eof, t_data *data)
{
    int fd;

    fd = open(eof, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror_fd(data);
    dup2(fd, 1);
}
void    redir_append(char *eof, t_data *data)
{
    int fd;

    fd = open(eof, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        perror_fd(data);
    dup2(fd, 1);
}

void    redir_input(char *eof, t_data *data)
{
    int fd;

    if (access(eof, F_OK) == 0)
    {
        fd = open(eof, O_RDONLY);
        if (fd == -1)
            perror_fd(data);
        dup2(fd, 0);
    }
    else
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(eof, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        data->new_st = 1;
        exit (1);
    }
}

void    execute_heredoc(char *eof, t_data *data)
{
    int pipe_fd[2];
    char *tmp;
    int quoted;
    char *line = NULL;

    if (pipe(pipe_fd) == -1)
        perror_pipe(data);
    quoted = check_quoted(eof);
    tmp = ft_strdup(eof);
    if (quoted != 0)
        eof = handle_quoted(tmp);
    while (1)
    {
        signal(SIGINT, signal_herdoc);
        line = readline("> ");
        if (quoted == 0)
            expand_herdoc(&line, data);
        if (!line)
        {
            free(line); //if i press cntl+/D
            break;
        }
        if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
        {
            free(line);
            break ;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        ft_putstr_fd("\n", pipe_fd[1]);
        free(line);
    }
    dup2(pipe_fd[0], 0);
    close(pipe_fd[1]);
    free(tmp);
}

void    execute_redir(t_cmd *cmd, t_data *data)
{
    int pid_f;
    int i;

    i = 0;
    pid_f = fork();
    if (pid_f == -1)
        perror("fork");
    else if (pid_f == 0)
    {
        while (cmd->redir_nbr != 0)
        {
            if (ft_strcmp(cmd[0].redir[i].redi, ">") == 0)
                redir_output(cmd[0].redir[i].eof, data);
            else if (ft_strcmp(cmd[0].redir[i].redi, ">>") == 0)
                redir_append(cmd[0].redir[i].eof, data);
            else if (ft_strcmp(cmd[0].redir[i].redi, "<") == 0)
                redir_input(cmd[0].redir[i].eof, data);
            else if (ft_strcmp(cmd[0].redir[i].redi, "<<") == 0)
                execute_heredoc(cmd[0].redir[i].eof, data);
            cmd->redir_nbr--;
            i++;
        }
        found_cmd(cmd, 0 , data);
    }
    else
        wait(&data->new_st); 
}