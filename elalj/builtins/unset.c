/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:53:23 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/11 19:29:17 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_not_identifier_un(char *line, t_data *data)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->new_st = 1;
}

void	remove_key(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (!data->key_env[i + 1])
		data->c_env[i] = NULL;
	else
	{
		while (data->key_env[i] != NULL)
		{
			get_key(data, 0);
			if (ft_strcmp(line, data->key_env[i]) == 0)
			{
				while (data->c_env[i] != NULL)
				{
					data->c_env[i] = data->c_env[i + 1];
					i++;
				}
			}
			i++;
		}
	}
}

int	count_arg_un(t_cmd *cmd, int i)
{
	int	arg;

	arg = 1;
	while (cmd[i].argu[arg] != NULL)
		arg++;
	return (arg);
}

void	my_unset(t_cmd *cmd, t_data *data, int i)
{
	int	arg;

	get_key(data, 0);
	arg = count_arg_un(cmd, i);
	arg--;
	while (arg != 0)
	{
		if (ft_isalpha(strback(cmd[i].argu[arg])[0]) || ft_isalnum(strback(cmd[i].argu[arg]))
			|| ft_search(cmd[i].argu[arg], '='))
			print_not_identifier_un(cmd[i].argu[arg], data);
		else
			remove_key(data, cmd[i].argu[arg]);
		arg--;
	}
}
