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

void	my_echo(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != 0)
			printf(" ");
		i++;
	}
}

void	handle_my_echo(char **line)
{
	int	i;

	i = 1;
	if (line[i] && line[i][0] == '-' && line[i][1] == 'n')
		my_echo(line, i + 1);
	else if (line[i])
	{
		my_echo(line, i);
		printf("\n");
	}
	else
		printf("\n");
}
