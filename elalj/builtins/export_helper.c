/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:24:44 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 11:24:46 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_not_identifier_ex(char *line, t_data *data)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->new_st = 1;
}

void	get_key(t_data *data, int n_arg)
{
	int		i;
	char	*tmp;

	if (n_arg > 0)
		data->key_env = ft_realloc(data->key_env,
				(len_arr(data->c_env) + n_arg));
	i = 0;
	while (data->c_env[i] != NULL)
	{
		tmp = strback(data->c_env[i]);
		free(data->key_env[i]);
		data->key_env[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	data->key_env[i] = NULL;
}

int	export_arg_count(t_cmd *cmd, int I)
{
	int		n_arg;
	int		i;
	char	*tmp;

	i = 1;
	n_arg = 0;
	while (cmd[I].argu[i] != NULL)
	{
		tmp = strback(cmd[I].args[i]);
		if (ft_isalnum(tmp)
			|| ft_isalpha(tmp[0]))
			i++;
		else
		{
			n_arg++;
			i++;
		}
		free(tmp);
	}
	return (n_arg);
}

int	export_total_arg(t_cmd *cmd, int I)
{
	int	i;

	i = 1;
	while (cmd[I].argu[i] != NULL)
		i++;
	i--;
	return (i);
}
