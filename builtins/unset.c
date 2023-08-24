/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:27:33 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/24 16:27:34 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_unset(char **line, t_data *data)
{
	int	n_arg;
	int	i;
	int removal;

	n_arg = 1;
	while(line[n_arg])
	{
		i = 0;
		while(data->c_env[i])
		{
			if (data->c_env[i] == line[n_arg])
			{
				removal = i;
				while (removal < len_arr(data->c_env) - 1)
				{
						data->c_env[removal] = line[]
				}
			}
		}
	}
}