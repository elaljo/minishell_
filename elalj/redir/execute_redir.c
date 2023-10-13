#include "../../minishell.h"

void    redir_output(char *eof)
{
    int fd;

    fd = open(eof, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror_fd();
    dup2(fd, 1);
    close (fd);
}
void    redir_append(char *eof)
{
    int fd;

    fd = open(eof, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        perror_fd();
    dup2(fd, 1);
    close(fd);
}

void    redir_input(char *eof)
{
    int fd;

    if (access(eof, F_OK) == 0)
    {
        fd = open(eof, O_RDONLY);
        if (fd == -1)
            perror_fd();
        dup2(fd, 0);
        close(fd);
    }
    else
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(eof, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
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
        perror_pipe();
    quoted = check_quoted(eof);
    tmp = ft_strdup(eof);
    signal(SIGINT, signal_herdoc);
    while (1)
    {
        line = readline("> ");
        if (*line == '\0')
            continue ;
        if (quoted != 0)
            eof = handle_quoted(tmp);
        if (ft_strcmp(line , eof) == 0 || !line)
            break ;
        if (quoted == 0)
            expand_herdoc(&line, data);
        write(pipe_fd[1], line, ft_strlen(line));
        ft_putstr_fd("\n", pipe_fd[1]);
        free(line);
    }
    free(line);
    dup2(pipe_fd[0], 0);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    free(tmp);
}

void    setup_redir(t_cmd *cmd, t_data *data, int e)
{
    int j;

    j = 0;
    while (cmd[e].redir_nbr != 0)
    {
        if (ft_strcmp(cmd[e].redii[j].redi, ">") == 0)
            redir_output(cmd[e].redii[j].eof);
        if (ft_strcmp(cmd[e].redii[j].redi, ">>") == 0)
            redir_append(cmd[e].redii[j].eof);
        if (ft_strcmp(cmd[e].redii[j].redi, "<") == 0)
            redir_input(cmd[e].redii[j].eof);
        if (ft_strcmp(cmd[e].redir[j].redi, "<<") == 0)
            execute_heredoc(cmd[e].redir[j].eof, data);
        cmd[e].redir_nbr--;
        j++;
    }
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
            if (ft_strcmp(cmd[0].redii[i].redi, ">") == 0)
                redir_output(cmd[0].redii[i].eof);
            else if (ft_strcmp(cmd[0].redii[i].redi, ">>") == 0)
                redir_append(cmd[0].redii[i].eof);
            else if (ft_strcmp(cmd[0].redii[i].redi, "<") == 0)
                redir_input(cmd[0].redii[i].eof);
            else if (ft_strcmp(cmd[0].redir[i].redi, "<<") == 0)
                execute_heredoc(cmd[0].redir[i].eof, data);
            cmd->redir_nbr--;
            i++;
        }
        found_cmd(cmd, 0 , data);
    }
    else
    {
        wait(&data->new_st);
        unsigned char *s;

        s = (unsigned char *)&data->new_st;
        if (s[0])
            data->new_st = s[0] + 128;
        else
            data->new_st = s[1];
    }
}
