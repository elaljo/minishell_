/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_get_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:05:29 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/17 17:45:50 by hait-sal         ###   ########.fr       */
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
/**
 * count the number of parts the command
 * have in order to allocate for it
 * @param tab all splitted tokens in a tab
 * @return the number of arguments that the command have.
 */
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

t_cmd	*get_cmds(char **tab)
{
	int		commande_len;
	t_cmd	*cmds;
	int		i;
	int		j;
	int		k;
	int		nbr;

	nbr = count_cmds(tab);
	cmds = malloc((nbr) * sizeof(t_cmd));
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
			cmds[j].args = malloc(2 * sizeof(char *));
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
			cmds[j].args = malloc((commande_len - cmds[j].redir_nbr + 1) * sizeof(char *));
			cmds[j].redir = malloc(cmds[j].redir_nbr * sizeof(t_redi));
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
						// printf("🟥🟥 ana f red-1🟥🟥\n");
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
					else if (ft_strcmp("<", tab[i]) == 0)
					{
						// printf("🟥🟥 ana f red-2🟥🟥\n");
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
					else if (ft_strcmp(">>", tab[i]) == 0)
					{
						// printf("🟥🟥 ana f red-3🟥🟥\n");
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
						cmds[j].redir[red].eof = ft_strdup(tab[i++]);
						red++;
						continue ;
					}
					else if (ft_strcmp(">", tab[i]) == 0)
					{
						// printf("🟥🟥 ana f red-4🟥🟥\n");
						cmds[j].redir[red].redi = ft_strdup(tab[i++]);
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
			cmds[j].cmd_len = cmd_len(cmds[j].args);
			// printf("🔴🌕🔴cmds[j].cmd_len --> %d🔴🌕🔴\n", cmds[j].cmd_len);
			j++;
		}
	}
	return (cmds);
}
