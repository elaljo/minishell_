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

void	handle_my_echo(t_cmd *cmd, int i)
{
	int a;

	a = 1;
	if (cmd[i].argu[0] && !cmd[i].argu[1])
		printf("\n");
	else if (cmd[i].argu[0] && cmd[i].argu[1][0] == '-' && cmd[i].argu[1][1] == 'n')
	{
		while (cmd[i].argu[0][0] == '-' && cmd[i].argu[0][1] == 'n')
			a++;
		my_echo(cmd, i, a);
	}
	else if (cmd[i].argu[a])
	{
		my_echo(cmd, i, a);
		printf("\n");
	}
}
