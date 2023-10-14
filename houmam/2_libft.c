/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_libft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:08:34 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 12:15:14 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cnt_wrds_p2(char *str, char c, t_sp *sp)
{
	if (str[sp->i] == 39)
	{
		sp->i++;
		sp->sq++;
	}
	if (str[sp->i] == 34)
	{
		sp->i++;
		sp->dq++;
	}
	if (str[sp->i] && sp->sq % 2 == 0 && sp->dq % 2 == 0)
	{
		while (str[sp->i] != c && str[sp->i])
		{
			if (str[sp->i] == 39)
				sp->sq++;
			if (str[sp->i] == 34)
				sp->dq++;
			sp->i++;
		}
		sp->wrds++;
	}
	else if (str[sp->i])
		sp->i++;
}

int	cnt_wrds(char *str, char c)
{
	t_sp	sp;

	sp.i = 0;
	sp.wrds = 0;
	sp.sq = 0;
	sp.dq = 0;
	while (str[sp.i])
	{
		while (str[sp.i] == c && sp.sq % 2 == 0 && sp.dq % 2 == 0 && str[sp.i])
			sp.i++;
		cnt_wrds_p2(str, c, &sp);
	}
	return (sp.wrds);
}

void	split_str_p2(char *str, char **tab, t_sp *sp, char c)
{
	if (sp->i > 0 && str[sp->i - 1] && \
		(str[sp->i - 1] == 34 || str[sp->i - 1] == 34))
		sp->start = sp->i - 1;
	sp->k = 0;
	while (str[sp->i])
	{
		if (str[sp->i] == c && sp->sq % 2 == 0 && sp->dq % 2 == 0)
			break ;
		if (str[sp->i] == 39)
			sp->sq++;
		if (str[sp->i] == 34)
			sp->dq++;
		sp->i++;
	}
	tab[sp->j] = ft_calloc(1, (sp->i - sp->start + 1) * sizeof(char));
	while (sp->start < sp->i)
	{
		tab[sp->j][sp->k] = str[sp->start];
		sp->k++;
		sp->start++;
	}
	if (str[sp->i] == 34 || str[sp->i] == 34)
		sp->i++;
	tab[sp->j][sp->k] = '\0';
	sp->j++;
}

void	split_str_p1(char *str, t_sp *sp, char c)
{
	while (str[sp->i] == c && sp->sq % 2 == 0 && sp->dq % 2 == 0 && str[sp->i])
		sp->i++;
	if (str[sp->i] == 39)
	{
		sp->i++;
		sp->sq++;
	}
	if (str[sp->i] == 34)
	{
		sp->i++;
		sp->dq++;
	}
}

char	**split_str(char *str, char c)
{
	t_sp	sp;
	char	**tab;

	sp.i = 0;
	sp.j = 0;
	sp.k = 0;
	sp.start = 0;
	sp.sq = 0;
	sp.dq = 0;
	sp.wrds = cnt_wrds(str, c);
	tab = ft_calloc(1, (sp.wrds + 1) * sizeof(char *));
	while (str[sp.i])
	{
		split_str_p1(str, &sp, c);
		if (str && str[sp.i])
		{
			sp.start = sp.i;
			split_str_p2(str, tab, &sp, c);
		}
	}
	tab[sp.j] = NULL;
	return (tab);
}
