/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:59:02 by moelalj           #+#    #+#             */
/*   Updated: 2023/09/04 18:59:03 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char **env, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			cmd->path = ft_strdup(ft_strchr(env[i], '='));
			break ;
		}
		i++;
	}
}

void	split_path(char **line, t_cmd *cmd)
{
	int		i;

	cmd->split_cmd = ft_split(cmd->path);
	i = 0;
	while (cmd->split_cmd[i] != NULL)
	{
		cmd->split_cmd[i] = ft_strjoin(cmd->split_cmd[i], "/");
		cmd->split_cmd[i] = ft_strjoin(cmd->split_cmd[i], line[0]);
		i++;
	}
}

char	*check_if_valid_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->split_cmd[i])
	{
		if (access(cmd->split_cmd[i], X_OK) == 0)
			return (cmd->split_cmd[i]);
		i++;
	}
	return (NULL);
}

void	execute_cmd(char **line, t_cmd *cmd)
{
	int		pid_f;
	char	*path;

	path = check_if_valid_cmd(cmd);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(line[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		pid_f = fork();
		if (pid_f == -1)
			perror("fork");
		else if (pid_f == 0)
			execve(path, line, NULL);
		else
			wait(NULL);
	}
}

void	found_cmd(char **line, t_cmd *cmd, char **env)
{
	if (opendir(line[0]) != NULL)
		open_dir_err(line);
	else if (access(line[0], X_OK) == -1 && ft_search(line[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(line[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	else if (access(line[0], X_OK) == 0 && ft_search(line[0], '/'))
		already_valid_path_exec(line);
	else
	{
		get_path(env, cmd);
		split_path(line, cmd);
		execute_cmd(line, cmd);
	}
}
