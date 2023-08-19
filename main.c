/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:09:36 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 15:09:37 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->c_env = NULL;
}

void copy_env(t_data *data, char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_strlen(env[i]);
		i++;
	}
	data->c_env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i] != NULL)
	{
		data->c_env[i] = ft_strdup(env[i]);
		i++;
	}
	data->c_env[i] = NULL;
}

int main(int ac, char *av[], char **env)
{
	(void)av;
	if (ac != 1)
		return (1);
	t_data data;
	char *line;
	char **sline;
	
	init_data(&data);
	copy_env(&data, env);
	while (1)
	{
		line = readline("minishell: ");
		if (line == NULL)
			return (0);
		sline = ft_split(line);
		add_history(line);
		if (is_builtin(sline) == 1)
			execute_builtin(sline, &data);
		free(line);
	}
	return (0);
}
