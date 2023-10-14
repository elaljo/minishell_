/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_others.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:47:26 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 08:55:00 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_trim(char **str, int i)
{
	int		start;
	int		j;
	char	*tmp;
	int		end;

	if (str[i][0] != 0)
	{
		start = 0;
		j = 0;
		tmp = ft_strdup(str[i]);
		end = ft_strlen(str[i]) - 1;
		while (tmp[start] == ' ')
			start++;
		while (tmp[end] == ' ')
			end--;
		free(str[i]);
		str[i] = ft_calloc(1, end - start + 1 + 1);
		while (start < end + 1)
		{
			str[i][j] = tmp[start];
			j++;
			start++;
		}
		free(tmp);
	}
}

char	**rm_empty(char **tab)
{
	char	**tmp;
	int		cnt;
	int		i;

	tmp = tab_dup(tab);
	ft_str_free(tab);
	i = 0;
	cnt = 0;
	while (tmp[i] != NULL)
	{
		if (tmp[i][0] == '\0')
			cnt++;
		i++;
	}
	tab = ft_calloc(1, (i - cnt + 1) * sizeof(char *));
	rm_empty_p2(tab, tmp, &i, &cnt);
	tab[i] = NULL;
	ft_str_free(tmp);
	return (tab);
}

void	rm_empty_p2(char **tab, char **tmp, int *i, int *cnt)
{
	*i = 0;
	(*cnt) = 0;
	while (tmp[(*cnt)] != NULL)
	{
		if (tmp[(*cnt)][0] == 0)
		{
			(*cnt)++;
			continue ;
		}
		tab[*i] = ft_strdup(tmp[(*cnt)]);
		(*i)++;
		(*cnt)++;
	}
}

char	**tab_dup(char **tab)
{
	int		i;
	char	**dup;

	i = 0;
	while (tab[i] != NULL)
		i++;
	dup = ft_calloc(1, (i + 1) * sizeof(char *));
	i = 0;
	while (tab[i] != NULL)
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	free_cmds(t_cmd *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds[0].argu_nbr)
	{
		ft_str_free(cmds[i].argu);
		if (cmds[i].redir_nbr != 0)
		{
			j = 0;
			while (j < cmds[i].redir_nbr)
			{
				free(cmds[i].redir[j].eof);
				free(cmds[i].redir[j].redi);
				free(cmds[i].redii[j].eof);
				free(cmds[i].redii[j].redi);
				j++;
			}
			free(cmds[i].redir);
			free(cmds[i].redii);
		}
		free(cmds[i].path);
		i++;
	}
	free(cmds);
}
