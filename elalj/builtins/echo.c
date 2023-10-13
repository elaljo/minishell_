/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:45:46 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/11 20:04:17 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_echo(t_cmd *cmd, int i, int a)
{
	while (cmd[i].argu[a])
	{
		printf("%s", cmd[i].argu[a]);
		if (cmd[i].argu[a + 1] != 0)
			printf(" ");
		a++;
	}
}

int	check_first_n(t_cmd *cmd, int i)
{
	int	e;

	e = 2;
	while (cmd[i].argu[1][e])
	{
		if (cmd[i].argu[1][e] == 'n')
			e++;
		else
			return (1);
	}
	return (0);
}

int	check_n_n(t_cmd *cmd, int i, int a)
{
	int	e;

	e = 2;
	if (ft_strncmp(cmd[i].argu[a], "-n", 2) == 0)
	{
		while (cmd[i].argu[a][e])
		{
			if (cmd[i].argu[a][e] != 'n')
				return (1);
			e++;
		}
	}
	else
		return (1);
	return (0);
}

void	option_n(t_cmd *cmd, int i)
{
	int	a;

	a = 1;
	while (cmd[i].argu[a])
	{
		if (a == 1)
		{
			if (check_first_n(cmd, i) == 1)
			{
				my_echo(cmd, i, a);
				printf("\n");
				return ;
			}
		}
		else
		{
			if (check_n_n(cmd, i, a) != 0)
			{
				my_echo(cmd, i, a);
				return ;
			}
		}
		a++;
	}
}

void	handle_my_echo(t_cmd *cmd, int i)
{
	int	a;

	a = 1;
	if (cmd[i].argu[0] && !cmd[i].argu[1])
		printf("\n");
	else if (ft_strncmp(cmd[i].argu[a], "-n", 2) == 0)
		option_n(cmd, i);
	else if (cmd[i].argu[a])
	{
		my_echo(cmd, i, a);
		printf("\n");
	}
}
