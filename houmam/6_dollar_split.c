/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 05:46:53 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/16 05:46:53 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_split_p0(char *str, t_ndx *s)
{
	while (str[s->i])
	{
		if (str[s->i] == '$' && str[s->i + 1] && is_var(str[s->i + 1]) == 1)
		{
			s->i++;
			while (str[s->i] && is_var(str[s->i]) == 1)
				s->i++;
			break ;
		}
		else
		{
			while (str[s->i])
			{
				if (str[s->i] == '$' && str[s->i + 1] && \
					is_var(str[s->i + 1]) == 1)
					break ;
				s->i++;
			}
			break ;
		}
	}
}

char	**dollar_split(char *str)
{
	t_ndx	s;
	char	**tab;

	s.i = 0;
	s.j = 0;
	s.k = 0;
	s.start = 0;
	s.len = cnt_dollars(str) + 1;
	tab = ft_calloc(1, s.len * sizeof(char *));
	while (s.len > 1 && str[s.i])
	{
		s.start = s.i;
		dollar_split_p0(str, &s);
		tab[s.j] = ft_calloc(1, s.i - s.start + 1);
		s.k = 0;
		while (s.start < s.i)
		{
			tab[s.j][s.k] = str[s.start];
			s.k++;
			s.start++;
		}
		s.j++;
	}
	tab[s.j] = NULL;
	return (tab);
}
