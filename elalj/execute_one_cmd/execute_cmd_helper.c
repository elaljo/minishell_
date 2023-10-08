/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 00:03:47 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/05 20:58:46 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data_structs(t_data *data)
{
	data->c_env = NULL;
	data->len_env = 0;
	data->key_env = NULL;
}

void	open_dir_err(t_cmd *cmd, int i, int j)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[i].args[j], 2);
	ft_putstr_fd(": is a directory\n", 2);
	exit (126);
}
