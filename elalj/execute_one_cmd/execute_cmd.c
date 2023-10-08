/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:59:02 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/05 20:59:19 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	executing_one_cmd(t_cmd *cmd, int i, t_data *data, int j)
{
	int	pid_f;

	pid_f = fork();
	if (pid_f == -1)
		perror_fork(data);
	if (pid_f == 0)
		found_cmd(cmd, i, data, j);
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
		exit (127);
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

void	execute_cmd(t_cmd *cmd, int i, t_data *data, int j)
{
	if (cmd[i].path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[i].args[j], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	if (execve(cmd[i].path, &cmd[i].args[j], data->c_env) == -1)
		perror_execve(data);
}

void	found_cmd(t_cmd *cmd, int i, t_data *data, int j)
{
	if (*cmd[i].args[j] == '\0' && !cmd[i].args[j])
		return ;
	if (is_builtin(cmd[i].args[0]) == 1)
	{
		execute_builtin(cmd, data, i);
		exit (0);
	}
	if (opendir(cmd[i].args[j]) != NULL)
		open_dir_err(cmd, i, j);
	else if (access(cmd[i].args[j], X_OK) == -1 && ft_search(cmd[i].args[j], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[i].args[j], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		exit (127);
	}
	else if (access(cmd[i].args[j], X_OK) == 0 && ft_search(cmd[i].args[j], '/'))
	{
		if (execve(cmd[i].args[j], &cmd[i].args[j], data->c_env) == -1)
			perror_execve(data);
	}
	else
	{
		cmd[i].path = get_cmd_path(data, cmd[i].args[j]);
		execute_cmd(cmd, i, data, j);
	}
}
