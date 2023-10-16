/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:39:10 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/11 20:00:11 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	same_key(t_data *data, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->key_env[i] != NULL)
	{
		tmp = strback(line);
		if (ft_strcmp(tmp, data->key_env[i]) == 0)
		{
			if (ft_search(tmp, '='))
			{
				free(data->c_env[i]);
				data->c_env[i] = ft_strdup(tmp);
			}
			free(tmp);
			return (1);
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}

void	if_there_var(t_cmd *cmd, t_data *data, int I)
{
	int		n_arg;
	int		i;
	int		p;
	int		len_env;
	char	*tmp;

	get_key(data, 0);
	len_env = len_arr(data->c_env);
	n_arg = export_arg_count(cmd, I);
	data->c_env = ft_realloc(data->c_env, (len_env + n_arg));
	i = 1;
	p = export_total_arg(cmd, I);
	while (p != 0)
	{
		tmp = strback(cmd[I].argu[i]);
		if (ft_isalpha(tmp[0]) || ft_isalnum(tmp))
			print_not_identifier_ex(cmd[I].argu[i], data);
		else if (!same_key(data, cmd[I].argu[i]))
		{
			data->c_env[len_env] = ft_strdup(cmd[I].argu[i]);
			len_env = len_arr(data->c_env);
		}
		i++;
		p--;
		free(tmp);
		tmp = NULL;
		get_key(data, len_env);
	}
}

void	my_export(t_cmd *cmd, t_data *data, int I)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (cmd[I].argu[0] && !cmd[I].argu[1])
	{
		while (data->c_env[i] != NULL)
		{
			printf("declare -x ");
			print_export(data, i, check);
			check = 0;
			printf("\n");
			i++;
		}
	}
	else
		if_there_var(cmd, data, I);
}

void	print_export(t_data *data, int i, int check)
{
	int	j;

	j = 0;
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
