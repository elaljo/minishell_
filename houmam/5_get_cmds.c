/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:05:29 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 15:51:41 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*get_cmds(char **tab, t_data *data)
{
	int		comnd_len;
	t_cmd	*cmds;
	t_ndx	n;

	n.nbr = count_cmds(tab);
	cmds = ft_calloc(1, (n.nbr) * sizeof(t_cmd));
	n.i = 0;
	n.j = 0;
	while (tab[n.i] != NULL)
	{
		if (tab[n.i][0] == '|')
		{
			n.i++;
			continue ;
		}
		comnd_len = cmd_len(&tab[n.i]);
		if (comnd_len == 1)
			get_cmds_p0(tab, &comnd_len, cmds, &n);
		else if (comnd_len != 1)
		{
			get_cmds_p4(tab, &comnd_len, cmds, &n);
			get_cmds_p5(data, cmds, &n);
		}
	}
	return (cmds);
}

void	get_cmds_p0(char **tab, int *comnd_len, t_cmd *cmds, t_ndx *n)
{
	cmds[n->j].cmd_len = *comnd_len;
	cmds[n->j].argu_nbr = n->nbr;
	cmds[n->j].redir_nbr = cnt_redir(&tab[n->i]);
	if (cmds[n->j].redir_nbr != 0)
	{
		cmds[n->j].redir = \
		ft_calloc(cmds[n->j].redir_nbr, sizeof(t_redi));
		cmds[n->j].redir[0].redi = ft_strdup(tab[n->i]);
		cmds[n->j].redir[0].eof = NULL;
	}
	cmds[n->j].args = ft_calloc(1, 2 * sizeof(char *));
	cmds[n->j].args[0] = ft_strdup(tab[n->i]);
	cmds[n->j].args[1] = NULL;
	n->i++;
	n->j++;
}

void	get_cmds_p1(char **tab, int *comnd_len, t_cmd *cmds, t_ndx *n)
{
	cmds[n->j].cmd_len = *comnd_len;
	cmds[n->j].redir_nbr = cnt_redir(&tab[n->i]);
	cmds[n->j].argu_nbr = n->nbr;
	cmds[n->j].args = ft_calloc(1, \
	((*comnd_len) - cmds[n->j].redir_nbr + 1) * sizeof(char *));
	if (cmds[n->j].redir_nbr != 0)
		cmds[n->j].redir = \
		ft_calloc(cmds[n->j].redir_nbr, sizeof(t_redi));
	n->k = 0;
	n->red = 0;
}

int	get_cmds_p2(char **tab, t_cmd *cmds, t_ndx *n)
{
	if (ft_strcmp("<<", tab[n->i]) == 0)
	{
		cmds[n->j].redir[n->red].redi = ft_strdup(tab[n->i++]);
		if (tab[n->i])
			cmds[n->j].redir[n->red].eof = ft_strdup(tab[n->i++]);
		n->red++;
		return (1);
	}
	else if (ft_strcmp("<", tab[n->i]) == 0)
	{
		cmds[n->j].redir[n->red].redi = ft_strdup(tab[n->i++]);
		if (tab[n->i])
			cmds[n->j].redir[n->red].eof = ft_strdup(tab[n->i++]);
		n->red++;
		return (1);
	}
	else if (get_cmds_p3(tab, cmds, n) == 1)
		return (1);
	return (0);
}

int	get_cmds_p3(char **tab, t_cmd *cmds, t_ndx *n)
{
	if (ft_strcmp(">>", tab[n->i]) == 0)
	{
		cmds[n->j].redir[n->red].redi = ft_strdup(tab[n->i++]);
		if (tab[n->i])
			cmds[n->j].redir[n->red].eof = ft_strdup(tab[n->i++]);
		n->red++;
		return (1);
	}
	else if (ft_strcmp(">", tab[n->i]) == 0)
	{
		cmds[n->j].redir[n->red].redi = ft_strdup(tab[n->i++]);
		if (tab[n->i])
			cmds[n->j].redir[n->red].eof = ft_strdup(tab[n->i++]);
		n->red++;
		return (1);
	}
	return (0);
}
