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
		perror("getcwd");
}

void	export_pwd(t_data *data)
{
	int		i;
	char	c_dir[256];
	char	*c_path;

	c_path = "PWD=";
	c_path = ft_strjoin(c_path, getcwd(c_dir, 256));
	if (!c_path)
		perror("getcwd");
	i = 0;
	while (data->c_env[i] != NULL)
	{
		if (ft_strncmp(data->c_env[i], "PWD", 3) == 0)
		{
			data->c_env[i] = c_path;
			break ;
		}
		i++;
	}
}
