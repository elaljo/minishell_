/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_cmds_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:53:57 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 15:51:07 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cmds_p4(char **tab, int *comnd_len, t_cmd *cmds, t_ndx *n)
{
	get_cmds_p1(tab, comnd_len, cmds, n);
	while (n->k < (*comnd_len) && tab[n->i] != NULL)
	{
		if (tab[n->i][0] == '|')
			break ;
		if (cmds[n->j].redir_nbr != 0)
			if (get_cmds_p2(tab, cmds, n) == 1)
				continue ;
		cmds[n->j].args[n->k] = ft_strdup(tab[n->i]);
		n->k++;
		n->i++;
	}
	cmds[n->j].args[n->k] = NULL;
}

void	get_cmds_p5(t_data *data, t_cmd *cmds, t_ndx *n)
{
	if (cmds[n->j].redir_nbr != 0)
		cp_redir(cmds, n->j, data);
	cmds[n->j].cmd_len = cmd_len(cmds[n->j].args);
	n->j++;
}

int	count_cmds(char **tab)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 1;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|' && i != 0)
			cnt++;
		i++;
	}
	return (cnt);
}

int	cmd_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|' || tab[i] == NULL)
			break ;
		i++;
	}
	return (i);
}

void	cp_redir(t_cmd *cmds, int j, t_data *data)
{
	int	i;

	i = 0;
	if (cmds[j].redir_nbr != 0)
	{
		cmds[j].redii = ft_calloc(cmds[j].redir_nbr, sizeof(t_redi));
		while (i < cmds[j].redir_nbr)
		{
			cmds[j].redii[i].eof = ft_strdup(cmds[j].redir[i].eof);
			cmds[j].redii[i].redi = ft_strdup(cmds[j].redir[i].redi);
			expand_redir(cmds, j, i, data);
			i++;
		}
	}
}
