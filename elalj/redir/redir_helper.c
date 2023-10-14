/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:23:47 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 13:23:48 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_redir(t_cmd *cmd, t_data *data, int e)
{
	int	j;

	j = 0;
	while (cmd[e].redir_nbr != 0)
	{
		if (ft_strcmp(cmd[e].redii[j].redi, ">") == 0)
			redir_output(cmd[e].redii[j].eof);
		if (ft_strcmp(cmd[e].redii[j].redi, ">>") == 0)
			redir_append(cmd[e].redii[j].eof);
		if (ft_strcmp(cmd[e].redii[j].redi, "<") == 0)
			redir_input(cmd[e].redii[j].eof);
		if (ft_strcmp(cmd[e].redir[j].redi, "<<") == 0)
			execute_heredoc(cmd[e].redir[j].eof, data);
		cmd[e].redir_nbr--;
		j++;
	}
}

void	exit_status_func(t_data *data)
{
	unsigned char	*s;

	wait(&data->new_st);
	s = (unsigned char *)&data->new_st;
	if (s[0])
		data->new_st = s[0] + 128;
	else
		data->new_st = s[1];
}
