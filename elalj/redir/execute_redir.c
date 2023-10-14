/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:00:34 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 13:34:07 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_output(char *eof)
{
	int	fd;

	fd = open(eof, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror_fd();
	dup2(fd, 1);
	close (fd);
}

void	redir_append(char *eof)
{
	int	fd;

	fd = open(eof, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror_fd();
	dup2(fd, 1);
	close(fd);
}

void	redir_input(char *eof)
{
	int	fd;

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

int	execute_heredoc(char *eof, t_data *data)
{
	data->line = NULL;
	if (pipe(data->pipe_fd) == -1)
		perror_pipe();
	data->quoted = check_quoted(eof);
	data->tmp = ft_strdup(eof);
	signal(SIGINT, signal_herdoc);
	while (1)
	{
		data->line = readline("> ");
		if (*data->line == '\0')
			continue ;
		if (data->quoted != 0)
			eof = handle_quoted(data->tmp);
		if (ft_strcmp(data->line, eof) == 0 || !data->line)
			break ;
		if (data->quoted == 0)
			expand_herdoc(&data->line, data);
		write(data->pipe_fd[1], data->line, ft_strlen(data->line));
		ft_putstr_fd("\n", data->pipe_fd[1]);
		free(data->line);
	}
	return ((free(data->line), free(data->tmp),
			dup2(data->pipe_fd[0], 0), close(data->pipe_fd[1]),
			close(data->pipe_fd[0]), 1));
}

void	execute_redir(t_cmd *cmd, t_data *data)
{
	int	pid_f;
	int	i;

	i = 0;
	pid_f = fork();
	if (pid_f == -1)
		perror("fork");
	else if (pid_f == 0)
	{
		while (cmd->redir_nbr-- != 0)
		{
			if (ft_strcmp(cmd[0].redii[i].redi, ">") == 0)
				redir_output(cmd[0].redii[i].eof);
			else if (ft_strcmp(cmd[0].redii[i].redi, ">>") == 0)
				redir_append(cmd[0].redii[i].eof);
			else if (ft_strcmp(cmd[0].redii[i].redi, "<") == 0)
				redir_input(cmd[0].redii[i].eof);
			else if (ft_strcmp(cmd[0].redir[i].redi, "<<") == 0)
				execute_heredoc(cmd[0].redir[i].eof, data);
			i++;
		}
		found_cmd(cmd, 0, data);
	}
	else
		exit_status_func(data);
}
