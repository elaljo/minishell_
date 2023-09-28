/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:45:46 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 20:45:47 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_echo(t_cmd *cmd, int i, int a)
{
	while (cmd[i].args[a])
	{
		printf("%s", cmd[i].args[a]);
		if (cmd[i].args[a + 1] != 0)
			printf(" ");
		a++;
	}
}

void	handle_my_echo(t_cmd *cmd, int i)
{
	int	a;

	a = 1;
	if (!cmd[i].args[1])
		printf("\n");
	else if (cmd[i].args[0] && cmd[i].args[1][0] == '-' && cmd[i].args[1][1] == 'n')
	{
		while (cmd[i].args[a][0] == '-' && cmd[i].args[a][1] == 'n')
			a++;
		my_echo(cmd, i, a);
	}
	else if (cmd[i].args[a])
	{
		my_echo(cmd, i, a);
		printf("\n");
	}
}
