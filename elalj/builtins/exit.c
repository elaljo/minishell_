/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:48:56 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/11 20:05:49 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_if_exit_valid(char *line, t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(line, 2); 
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_str_free(data->c_env);
	ft_str_free(data->key_env);
	exit (255);
}

void	my_exit(t_cmd *cmd, int i, t_data *data)
{
	if (cmd[i].argu[0] && !cmd[i].argu[1])
	{
		ft_putstr_fd("exit\n", 1);
		ft_str_free(data->c_env);
		ft_str_free(data->key_env);
		exit (0);
	}
	else if (cmd[i].argu[1])
	{
		if (valid_num(cmd[i].argu[1]) == 0 || (ft_strlen(cmd[i].argu[1]) >= 19))
			print_if_exit_valid(cmd[i].argu[1], data);
		else if (cmd[i].argu[2])
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->new_st = 1;
			return ;
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			data->new_st = ft_atoi(cmd[i].argu[1]);
			ft_str_free(data->c_env);
			ft_str_free(data->key_env);
			exit(ft_atoi(cmd[i].argu[1]));
		}
	}
}
