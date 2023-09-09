/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:44:14 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 20:44:14 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}

void	my_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->c_env[i] != NULL)
	{
		if (ft_search(data->c_env[i], '=') == 1)
			printf("%s\n", data->c_env[i]);
		i++;
	}
}
