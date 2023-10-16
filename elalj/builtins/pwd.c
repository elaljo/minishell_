/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:45:08 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 20:45:09 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_pwd(void)
{
	char	c_dir[256];

	if (getcwd(c_dir, sizeof(c_dir)) != NULL)
		printf("%s\n", c_dir);
	else
	{
		perror("getcwd");
		exit (1);
	}
}

void	export_pwd(t_data *data)
{
	int		i;
	char	*curr_dir;
	char	*c_path;
	char	*tmp;

	curr_dir = getcwd(NULL, 256);
	c_path = ft_strjoin("PWD=", curr_dir);
	error_curr_dir(curr_dir);
	i = 0;
	while (data->c_env[i] != 0)
	{
		tmp = strback(data->c_env[i]);
		if (strcmp(tmp, "PWD") == 0)
		{
			free(data->c_env[i]);
			data->c_env[i] = ft_strdup(c_path);
		}
		i++;
		free(tmp);
	}
	free(c_path);
	free(curr_dir);
}

void	error_curr_dir(char *curr_dir)
{
	if (!curr_dir)
	{
		perror("getcwd");
		exit (1);
	}
}
