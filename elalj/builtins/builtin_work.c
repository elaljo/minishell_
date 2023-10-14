/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:04:54 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/11 19:57:28 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-')
			i++;
		else
			return (0);
	}
	return (1);
}

void	execute_builtin(t_cmd *cmd, t_data *data, int i)
{
	if (ft_strcmp(cmd[i].argu[0], "echo") == 0)
		handle_my_echo(cmd, i);
	else if (ft_strcmp(cmd[i].argu[0], "cd") == 0)
		my_cd(cmd, i, data);
	else if (ft_strcmp(cmd[i].argu[0], "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(cmd[i].argu[0], "export") == 0)
		my_export(cmd, data, i);
	else if (ft_strcmp(cmd[i].argu[0], "unset") == 0)
		my_unset(cmd, data, i);
	else if (ft_strcmp(cmd[i].argu[0], "env") == 0)
		my_env(data);
	else if (ft_strcmp(cmd[i].argu[0], "exit") == 0)
		my_exit(cmd, i, data);
}

int	is_builtin(char *cmd)
{
	char	*arr[8];
	int		i;

	arr[0] = "echo";
	arr[1] = "cd";
	arr[2] = "pwd";
	arr[3] = "exit";
	arr[4] = "env";
	arr[5] = "export";
	arr[6] = "unset";
	arr[7] = NULL;
	i = -1;
	while (arr[++i])
		if (ft_strcmp(cmd, arr[i]) == 0)
			return (1);
	return (0);
}
