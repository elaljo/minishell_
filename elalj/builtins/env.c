/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:44:14 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/05 20:51:26 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env(t_data *data, char **env)
{
	int	i;

	while (env[data->len_env] != NULL)
		data->len_env++;
	data->c_env = ft_calloc(data->len_env + 1, sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		data->c_env[i] = ft_strdup(env[i]);
		i++;
	}
	data->key_env = ft_calloc(data->len_env + 1, sizeof(char *));
}

void	my_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->c_env[i] == NULL)
	{
		ft_putstr_fd("minishell: env: No such file of directory\n", 2);
		data->new_st = 127;
	}
	while (data->c_env[i] != NULL)
	{
		if (ft_search(data->c_env[i], '=') == 1)
		{
			ft_putstr_fd(data->c_env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}
