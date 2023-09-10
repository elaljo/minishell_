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

int	count_arg_un(char **line)
{
	int	arg;

	arg = 1;
	while (line[arg] != NULL)
		arg++;
	arg--;
	return (arg);
}

void	my_unset(char **line, t_data *data)
{
	int	arg;

	get_key(data, 0);
	arg = count_arg_un(line);
	while (arg != 0)
	{
		if (ft_isalpha(strback(line[arg])[0]) || ft_isalnum(strback(line[arg]))
			|| ft_search(line[arg], '='))
			print_not_identifier_un(line[arg]);
		else
			remove_key(data, line[arg]);
		arg--;
	}
}
