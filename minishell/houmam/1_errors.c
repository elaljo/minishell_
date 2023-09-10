/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:05 by hait-sal          #+#    #+#             */
/*   Updated: 2023/08/30 10:50:14 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data_structs(t_data *data)
{
	data->c_env = NULL;
	data->len_env = 0;
	data->key_env = NULL;
	//cmd->cmd = NULL;
	//cmd->cmd_args = NULL;
	//cmd->path = NULL;
	//cmd->split_cmd = NULL;
}