/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:59:02 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/04 18:38:48 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executing_one_cmd(t_cmd *cmd, int i, t_data *data)
{
	int	pid_f;

	pid_f = fork();
	if (pid_f == -1)
		perror_fork();
	if (pid_f == 0)
		found_cmd(cmd, i, data);
	else
		wait(&g_exit_status);
}
char *get_cmd_path(t_data *data, char *cmd)
{
	int		i;
	char	*full_path;
	char	**path;
	char	*cmd_path;

	i = 0;
	full_path = NULL;
	while (data->c_env[i])
	{
		if (ft_strncmp(data->c_env[i], "PATH", 4) == 0)
		{
			full_path = ft_strdup(ft_strchr(data->c_env[i], '='));
			break ;
		}
		i++;
	}
	if (full_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 127;
	}
	path = ft_split(full_path);
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(path[i], cmd_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	return NULL;
}

void	execute_cmd(t_cmd *cmd, int i, t_data *data)
{
	if (cmd[i].path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[i].args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
		exit (127);
	}
	if (execve(cmd[i].path, cmd[i].args, data->c_env) == -1)
		perror_execve();
}

void	found_cmd(t_cmd *cmd, int i, t_data *data)
{
	if (is_builtin(cmd[i].args[0]) == 1)
	{
		execute_builtin(cmd, data, i);
		exit (0);
	}
	if (opendir(cmd[i].args[0]) != NULL)
		open_dir_err(cmd, i);
	else if (access(cmd[i].args[0], X_OK) == -1 && ft_search(cmd[i].args[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[i].args[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		g_exit_status = 127;
	}
	else if (access(cmd[i].args[0], X_OK) == 0 && ft_search(cmd[i].args[0], '/'))
	{
		if (execve(cmd[i].args[0], cmd[i].args, data->c_env) == -1)
			perror_execve();
	}
	else
	{
		cmd[i].path = get_cmd_path(data, cmd[i].args[0]);
		execute_cmd(cmd, i, data);
	}
}
