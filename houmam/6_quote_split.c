/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:39:07 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/15 17:39:07 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_split_p0(char *str, t_sp *z)
{
	if (str[z->i] == '\'' && z->i == 0)
		z->sq++;
	else if (str[z->i] == '"' && z->i == 0)
		z->dq++;
	else if (str[z->i] == '\'' && z->i != 0 && \
		str[z->i - 1] != '\\')
		z->sq++;
	else if (str[z->i] == '"' && z->i != 0 && \
		str[z->i - 1] != '\\')
		z->dq++;
}

int	quotes_split_p1(char *str, t_sp *z)
{
	if (str[z->i] == '\'' && z->i != 0 && str[z->i - 1] != '\\' \
		&& z->sq % 2 != 0 && z->dq % 2 != 0)
		z->sq++;
	else if (str[z->i] == '"' && z->i != 0 && str[z->i - 1] != '\\' \
		&& z->dq % 2 != 0 && z->sq % 2 != 0)
		z->dq++;
	else if (z->sq % 2 == 0 && z->i != 0 && str[z->i] == '\'' && \
		str[z->i - 1] != '\\')
		return (1);
	else if (z->dq % 2 == 0 && z->i != 0 && str[z->i] == '\"' && \
		str[z->i - 1] != '\\')
		return (1);
	else if (z->sq % 2 != 0 && z->i != 0 && str[z->i] == '\'' && \
		str[z->i - 1] != '\\' && str[z->i - 1] != '\'' && \
		str[z->i - 1] != '"')
		return (1);
	else if (z->dq % 2 != 0 && z->i != 0 && str[z->i] == '\"' && \
		str[z->i - 1] != '\\' && str[z->i - 1] != '\'' && \
		str[z->i - 1] != '"')
		return (1);
	else if (!str[z->i + 1])
		return (1);
	return (0);
}

void	quotes_split_p2(char *str, t_sp *z, char **tab)
{
	tab[z->j] = ft_calloc(1, (z->i - z->start + 2) * sizeof(char));
	z->k = 0;
	z->end = z->i;
	if ((str[z->i] == '\"' && z->dq % 2 == 0) || (str[z->i] == '\'' && \
		z->sq % 2 == 0) || str[z->i + 1] == '\0')
		z->end++;
	while (z->start < z->end)
	{
		tab[z->j][z->k] = str[z->start];
		z->k++;
		z->start++;
	}
	tab[z->j][z->k] = '\0';
	z->j++;
	if (str[z->i])
		z->i++;
}

void	quotes_split_p3(char *str, t_sp *z, char **tab)
{
	while (str[z->i])
	{
		z->start = z->i;
		if (z->i != 0 && ((str[z->i - 1] == '"' && z->dq % 2 != 0) || \
			(str[z->i - 1] == '\'' && z->sq % 2 != 0)))
			z->start--;
		while (str[z->i])
		{
			quotes_split_p0(str, z);
			if (quotes_split_p1(str, z) == 1)
				break ;
			z->i++;
		}
		quotes_split_p2(str, z, tab);
	}
	tab[z->j] = NULL;
}

char	**quotes_split(char *str)
{
	t_sp	z;
	char	**tab;

	z.start = 0;
	z.end = 0;
	z.i = 0;
	z.j = 0;
	z.sq = 0;
	z.dq = 0;
	z.len = cnt_exp(str) + 1;
	tab = ft_calloc(1, z.len * sizeof(char *));
	quotes_split_p3(str, &z, tab);
	return (tab);
}
