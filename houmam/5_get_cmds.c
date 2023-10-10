/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:05:29 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/10 05:42:36 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_cmds(char **tab)
{
	int i = 0;
	int cnt = 1;

	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
			cnt++;
		i++;
	}
	return (cnt);
}

int cmd_len(char **tab)
{
	int i = 0;

	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|' || tab[i] == NULL)
			break ;
		i++;
	}
	return (i);
}

t_cmd	*get_cmds(char **tab, t_data *data)
{
	int		commande_len;
	t_cmd	*cmds;
	int		i;
	int		j;
	int		k;
	int		nbr;

	nbr = count_cmds(tab);
	cmds = ft_calloc(1,(nbr) * sizeof(t_cmd));
	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
		{
			i++;
			continue ;
		}
		commande_len = cmd_len(&tab[i]);
		if (commande_len == 1)
		{
			cmds[j].cmd_len = commande_len;
			cmds[j].args_nbr = nbr;
			cmds[j].redir_nbr = cnt_redir(&tab[i]);
			cmds[j].args = ft_calloc(1,2 * sizeof(char *));
			cmds[j].args[0] = ft_strdup(tab[i]);
			cmds[j].args[1] = NULL;
			j++;
			i++;
		}
		else if (commande_len != 1)
		{
			cmds[j].cmd_len = commande_len;
			cmds[j].redir_nbr = cnt_redir(&tab[i]);
			cmds[j].args_nbr = nbr;
			cmds[j].args = ft_calloc(1,(commande_len - cmds[j].redir_nbr + 1) * sizeof(char *));
			cmds[j].redir = ft_calloc(cmds[j].redir_nbr, sizeof(t_redi));
			k = 0;
			int red = 0;
			while (k < commande_len && tab[i] != NULL)
			{
				if (tab[i][0] == '|')
					break;
				if (cmds[j].redir_nbr != 0)
				{
					if (ft_strcmp("<<", tab[i]) == 0)
					{
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						if (tab[i])
							cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
					else if (ft_strcmp("<", tab[i]) == 0)
					{
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						if (tab[i])
							cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
					else if (ft_strcmp(">>", tab[i]) == 0)
					{
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						if (tab[i])
							cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
					else if (ft_strcmp(">", tab[i]) == 0)
					{
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						if (tab[i])
							cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
				}
				cmds[j].args[k] = ft_strdup(tab[i]);
				k++;
				i++;
			}
			cmds[j].args[k] = NULL;
			cp_redir(cmds, j, data);
			cmds[j].cmd_len = cmd_len(cmds[j].args);
			j++;
		}
	}
	return (cmds);
}


void	cp_redir(t_cmd *cmds, int j, t_data *data)
{
	int i = 0;
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

void	free_cmds(t_cmd *cmds)
{
	int i = 0;
	int j;
	
	while (i < cmds[0].args_nbr)
	{
		j = 0;
		while (cmds[i].args[j] != NULL)
		{
			free(cmds[i].args[j]);
			j++;
		}
		free(cmds[i].args);
		j = 0;
		while (j < cmds[i].redir_nbr)
		{
			free(cmds[i].redir[j].eof);
			free(cmds[i].redir[j].redi);
			free(cmds[i].redii[j].eof);
			free(cmds[i].redii[j].redi);
			j++;
		}
		free(cmds[i].path);
		i++;
	}
}
