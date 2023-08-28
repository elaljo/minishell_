/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:39:10 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/20 17:39:14 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_not_identifier_ex(char *line)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	get_key(t_data *data, int n_arg)
{
	int	i;

	data->key_env = realloc(data->key_env, sizeof(char *)
			* (len_arr(data->c_env) + n_arg + 1));
	i = 0;
	while (data->c_env[i] != NULL)
	{
		data->key_env[i] = ft_strdup(strback(data->c_env[i]));
		i++;
	}
	data->key_env[i] = 0;
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

void	if_there_var(char **line, t_data *data)
{
	int	n_arg;
	int	i;
	int	len_env;

	len_env = len_arr(data->c_env);
	i = 1;
	n_arg = 0;
	while (line[i] != NULL)
	{
		if (ft_isalnum(strback(line[i])) || ft_isalpha(strback(line[i])[0]))
			i++;
		else
		{
			n_arg++;
			i++;
		}
	}
	i--;
	data->c_env = realloc(data->c_env, sizeof(char *) * (len_env + n_arg + 1));
	int	p = i;
	i = 1;
	while (p != 0)
	{
		if (ft_isalpha(strback(line[i])[0]) || ft_isalnum(strback(line[i])))
		{
			print_not_identifier_ex(line[i]);
			i++;
			p--;
		}
		else if (same_key(data, line[i]) == 1)
		{
			i++;
			p--;
		}
		else
		{
			data->c_env[len_env] = ft_strdup(line[i]);
			data->c_env[len_env + 1] = NULL;
			i++;
			p--;
			len_env = len_arr(data->c_env);
		}
		get_key(data, n_arg);
	}
}

void	my_export(char **line, t_data *data)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	i = 0;
	if (line[0] && !line[1])
	{
		while (data->c_env[i] != NULL)
		{
			printf("declare -x ");
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
			check = 0;
			printf("\n");
			i++;
		}
		get_key(data, 0);
	}
	else
		if_there_var(line, data);
}
