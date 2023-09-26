/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:53:23 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/27 16:53:29 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_not_identifier_un(char *line)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	remove_key(t_data *data, char *line)
{
	int	i;

	i = 0;
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
		else
			i++;
	}
}

int	count_arg_un(t_cmd *cmd)
{
	int	arg;

	arg = 1;
	while (cmd[0].args[arg] != NULL)
		arg++;
	return (arg);
}

void	my_unset(t_cmd *cmd, t_data *data, int i)
{
	int	arg;

	get_key(data, 0);
	arg = count_arg_un(cmd);
	while (arg != 0)
	{
		if (ft_isalpha(strback(cmd[i].args[arg - 1])[0]) || ft_isalnum(strback(cmd[i].args[arg - 1]))
			|| ft_search(cmd[i].args[arg - 1], '='))
			print_not_identifier_un(cmd[i].args[arg - 1]);
		else
			remove_key(data, cmd[i].args[arg - 1]);
		arg--;
	}
}
