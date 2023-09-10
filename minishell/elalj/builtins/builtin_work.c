/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:04:54 by moelalj           #+#    #+#             */
/*   Updated: 2023/09/09 17:09:56 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	execute_builtin(t_cmd *cmd, t_data *data)
{
	(void)data;
	if (ft_strcmp(cmd[0].cmd, "echo") == 0)
		handle_my_echo(cmd);
	else if (ft_strcmp(cmd[0].cmd, "cd") == 0)
		my_cd(cmd);
	else if (ft_strcmp(cmd[0].cmd, "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(cmd[0].cmd, "export") == 0)
		my_export(cmd, data);
	else if (ft_strcmp(cmd[0].cmd, "unset") == 0)
		my_unset(cmd, data);
	else if (ft_strcmp(cmd[0].cmd, "env") == 0)
		my_env(data);
	else if (ft_strcmp(cmd[0].cmd, "exit") == 0)
		my_exit(cmd);
}

int	is_builtin(t_cmd *cmd)
{
	char	*arr[] = {"echo", "cd", "pwd", "exit", "env", "export", "unset", NULL};
	int		i;

	i = -1;
	while (arr[++i])
	{
		if (ft_strcmp(cmd[0].cmd, arr[i]) == 0)
			return (1);
	}
	return (0);
}
