/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 00:03:47 by moelalj           #+#    #+#             */
/*   Updated: 2023/09/05 00:03:48 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data_structs(t_data *data)
{
	data->c_env = NULL;
	data->len_env = 0;
	data->key_env = NULL;
}

void	open_dir_err(t_cmd *cmd, int i)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[i].args[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
}
