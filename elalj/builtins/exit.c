/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:48:56 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 20:48:56 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_if_exit_valid(char *line)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(line, 2); 
	ft_putstr_fd(": numeric argument required\n", 2);
	exit (255);
}

void	my_exit(t_cmd *cmd, int i)
{
	if (cmd[i].args[0] && !cmd[i].args[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
	else if (cmd[i].args[1])
	{
		if (valid_num(cmd[i].args[1]) == 0 || (ft_strlen(cmd[i].args[1]) == 19))
			print_if_exit_valid(cmd[i].args[1]);
		else if (cmd[i].args[2])
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(ft_atoi(cmd[i].args[1]));
		}
	}
}
