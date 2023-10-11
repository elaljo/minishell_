/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:39:10 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/05 20:58:08 by hait-sal         ###   ########.fr       */
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
	int	i;

	data->key_env = realloc(data->key_env, sizeof(char *) ////
			* (len_arr(data->c_env) + n_arg + 1));
	i = 0;
	while (data->c_env[i] != NULL)
	{
		data->key_env[i] = ft_strdup(strback(data->c_env[i]));
		i++;
	}
	data->key_env[i] = NULL;
}

int	same_key(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (data->key_env[i] != NULL)
	{
		if (ft_strcmp(strback(line), data->key_env[i]) == 0)
		{
			if (ft_search(line, '='))
				data->c_env[i] = ft_strdup(line);
			return (1);
		}
		i++;
	}
	return (0);
}

void	if_there_var(t_cmd *cmd, t_data *data, int I)
{
	int	n_arg;
	int	i;
	int	j;
	int	len_env;

	len_env = len_arr(data->c_env);
	i = 1;
	j = 0;
	n_arg = 0;
	while (cmd[I].args[i] != NULL)
	{
		if (ft_isalnum(strback(cmd[I].args[i])) || ft_isalpha(strback(cmd[I].args[i])[0]))
		{
			j++;
			i++;
		}
		else
		{
			j++;
			n_arg++;
			i++;
		}
	}
	data->c_env = realloc(data->c_env, sizeof(char *) * (len_env + n_arg + 1));
	int	p = j;
	i = 1;
	while (p != 0)
	{
		if (ft_isalpha(strback(cmd[I].args[i])[0]) || ft_isalnum(strback(cmd[I].args[i])))
		{
			print_not_identifier_ex(cmd[I].args[i], data);
			j++;
			i++;
			p--;
		}
		else if (same_key(data, cmd[I].args[i]) == 1)
		{
			i++;
			j++;
			p--;
		}
		else
		{
			data->c_env[len_env] = ft_strdup(cmd[I].args[i]);
			data->c_env[len_env + 1] = NULL;
			i++;
			j++;
			p--;
			len_env = len_arr(data->c_env);
		}
		get_key(data, n_arg);
	}
}

void	my_export(t_cmd *cmd, t_data *data, int I)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	i = 0;
	if (cmd[I].args[0] && (!cmd[I].args[1]))
	{
		while (data->c_env[i] != NULL)
		{
			printf("declare -x ");
			j = 0;
			print_export(data, i, j, check);
			check = 0;
			printf("\n");
			i++;
		}
		get_key(data, 0);
	}
	else
		if_there_var(cmd, data, I);
}

void print_export(t_data *data ,int i, int j, int check)
{
	while (data->c_env[i][j] != '\0')
		{
			printf("%c", data->c_env[i][j]);
			if (data->c_env[i][j] == '=' && check == 0)
			{
				check = 1;
				printf("\"");
			}
			if (data->c_env[i][j + 1] == '\0' && check == 1)
				printf("\"");
			j++;
		}
}
