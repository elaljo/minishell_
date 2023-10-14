/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:03:46 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 20:03:49 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_status(t_data *data)
{
	data->old_st = data->new_st;
	data->new_st = 0;
}

void	ctrl_d(t_data *data, char *input_string)
{
	(void)data;
	if (!input_string)
	{
		printf("exit\n");
		exit (0);
	}
}

void	executer(t_cmd *cmds, t_data *data)
{
	if (cmds->redir_nbr != 0 && cmds->argu_nbr == 1)
		execute_redir(cmds, data);
	else if (cmds->argu_nbr == 1)
	{
		if (cmds[0].argu[0] && is_builtin(cmds[0].argu[0]) == 1 \
			&& cmds->argu_nbr == 1)
			execute_builtin(cmds, data, 0);
		else
			executing_one_cmd(cmds, 0, data);
	}
	else if (cmds->argu_nbr > 1)
		execute_pipe(cmds, data);
}
