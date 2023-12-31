/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_sp_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:16:19 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 12:19:33 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redir(char *str, char **tab, t_ndx *ndx, t_quote quote)
{
	if (str[ndx->i + 1] != 0 && ((str[ndx->i] == '>' && \
		str[ndx->i + 1] == '>') || (str[ndx->i] == '<' && \
		str[ndx->i + 1] == '<')) && quote.sq % 2 == 0 && quote.dq % 2 == 0)
	{
		tab[ndx->j] = ft_calloc(1, 3 * sizeof(char));
		tab[ndx->j][0] = str[ndx->i];
		tab[ndx->j][1] = str[ndx->i + 1];
		tab[ndx->j][2] = 0;
		(ndx->j)++;
		(ndx->i)++;
		ndx->start = ndx->i + 1;
		return (1);
	}
	else if ((str[ndx->i] == '>' || str[ndx->i] == '<') \
		&& quote.sq % 2 == 0 && quote.dq % 2 == 0)
	{
		tab[ndx->j] = ft_calloc(1, 2 * sizeof(char));
		tab[ndx->j][0] = str[ndx->i];
		tab[ndx->j][1] = 0;
		(ndx->j)++;
		ndx->start = ndx->i + 1;
		return (1);
	}
	return (0);
}

int	handle_pipe(char **tab, t_ndx *ndx, char *str)
{
	tab[ndx->j] = ft_calloc(1, 2 * sizeof(char));
	tab[ndx->j][0] = '|';
	tab[ndx->j][1] = '\0';
	(ndx->j)++;
	while (str[ndx->i] == ' ')
		ndx->i++;
	ndx->start = ndx->i + 1;
	return (1);
}
