/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 00:03:47 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/11 20:01:55 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data_structs(t_data *data)
{
	data->c_env = NULL;
	data->len_env = 0;
	data->key_env = NULL;
	data->new_st = 0;
}

void	open_dir_err(t_cmd *cmd, int i)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[i].argu[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
	exit (126);
}

void	printf_no_file_no_dir(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit (127);
}

char	*get_full_path(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->c_env[i])
	{
		if (ft_strncmp(data->c_env[i], "PATH", 4) == 0)
		{
			str = ft_strdup(ft_strchr(data->c_env[i], '='));
			break ;
		}
		i++;
	}
	return (str);
}
