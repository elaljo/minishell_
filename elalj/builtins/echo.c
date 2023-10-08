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

void	handle_my_echo(t_cmd *cmd, int i, int j)
{
	if (cmd[i].args[j] && !cmd[i].args[j + 1])
		printf("\n");
	else if (cmd[i].args[j] && cmd[i].args[j+1][0] == '-' && cmd[i].args[j+1][1] == 'n')
	{
		j++;
		while (cmd[i].args[j][0] == '-' && cmd[i].args[j][1] == 'n')
			j++;
		my_echo(cmd, i, j);
	}
	else if (cmd[i].args[j + 1])
	{
		my_echo(cmd, i, j + 1);
		printf("\n");
	}
}
