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

void	my_echo(t_cmd *cmd, int i)
{
	while (cmd[0].args[i])
	{
		printf("%s", cmd[0].args[i]);
		if (cmd[0].args[i + 1] != 0)
			printf(" ");
		i++;
	}
}

void	handle_my_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd[0].args[0] == NULL)
		printf("\n");
	else if (cmd[0].cmd && cmd[0].args[0][0] == '-' && cmd[0].args[0][1] == 'n')
		my_echo(cmd, i + 1);
	else if (cmd[0].args[i])
	{
		my_echo(cmd, i);
		printf("\n");
	}
}
