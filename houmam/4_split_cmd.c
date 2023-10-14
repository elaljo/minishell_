/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_split_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:07:17 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 13:45:12 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_p2(char *str, t_ndx *ndx, t_quote *quote, char **tab)
{
	if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
	(str[ndx->i] == ' ' || str[ndx->i] == '\t') && ndx->i != 0 && \
	str[ndx->i - 1] != '|' && str[ndx->i - 1] != ' ' && \
	str[ndx->i - 1] != '\t' && str[ndx->i - 1] != '>' && \
	str[ndx->i - 1] != '<' )
	{
		ndx->check_space = 1;
		return (1);
	}
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
		str[ndx->i] == '|')
		handle_pipe(tab, ndx, str);
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
	str[ndx->i] == '>' && str[ndx->i + 1] && str[ndx->i + 1] != '>')
		handle_redir(str, tab, ndx, *quote);
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
	str[ndx->i] == '<' && str[ndx->i + 1] && str[ndx->i + 1] != '<')
		handle_redir(str, tab, ndx, *quote);
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
	str[ndx->i] == '>' && str[ndx->i + 1] && str[ndx->i + 1] == '>')
		handle_redir(str, tab, ndx, *quote);
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
	str[ndx->i] == '<' && str[ndx->i + 1] && str[ndx->i + 1] == '<')
		handle_redir(str, tab, ndx, *quote);
	return (0);
}

int	split_p1(char *str, t_ndx *ndx, t_quote *quote, char **tab)
{
	if (ndx->i != 0 && str[ndx->i] == 39 && str[ndx->i - 1] != '\\')
		quote->sq++;
	else if (ndx->i != 0 && str[ndx->i] == 34 && str[ndx->i - 1] != '\\')
		quote->dq++;
	else if (ndx->i == 0 && str[ndx->i] == 39)
		quote->sq++;
	else if (ndx->i == 0 && str[ndx->i] == 34)
		quote->dq++;
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && \
	str[ndx->i + 1] != '\0' && (str[ndx->i + 1] == '|' || \
	(str[ndx->i + 1] == '<' && str[ndx->i] != '<') || \
	(str[ndx->i + 1] == '>' && str[ndx->i] != '>')))
	{
		ndx->pipe = 1;
		return (1);
	}
	else
	{
		if (split_p2(str, ndx, quote, tab) == 1)
			return (1);
	}
	return (0);
}

void	split_p3(char *str, t_ndx *ndx, t_quote *quote, char **tab)
{
	tab[ndx->j] = ft_calloc(1, (ndx->i - ndx->start + 2) * sizeof(char));
	if (ndx->pipe == 1)
		ndx->i++;
	ndx->k = 0;
	while (ndx->start < ndx->i)
	{
		tab[ndx->j][ndx->k] = str[ndx->start];
		ndx->start++;
		ndx->k++;
	}
	tab[ndx->j][ndx->k] = '\0';
	if (ndx->pipe == 1)
	{
		ndx->i--;
		ndx->pipe = 0;
	}
	if (ndx->check_space == 1)
	{
		while ((str[ndx->i] == ' ' || str[ndx->i] == '\t') && \
		quote->sq % 2 == 0 && quote->dq % 2 == 0)
			ndx->i++;
		ndx->i--;
		ndx->check_space = 0;
	}
	ndx->j++;
}

void	split_p0(char *str, t_ndx *ndx, t_quote *quote, char **tab)
{
	while (str[ndx->i])
	{
		if (ndx->i == 0)
		{
			while (str[ndx->i] == ' ' || str[ndx->i] == '\t')
				ndx->i++;
		}
		ndx->start = ndx->i;
		while (str[ndx->i])
		{
			if (split_p1(str, ndx, quote, tab) == 1)
				break ;
			if (str[ndx->i])
				ndx->i++;
		}
		split_p3(str, ndx, quote, tab);
		if (str[ndx->i])
			ndx->i++;
	}
	tab[ndx->j] = NULL;
}

char	**split(char *str)
{
	char	**tab;
	t_ndx	ndx;
	t_quote	quote;

	ndx.i = 0;
	ndx.j = 0;
	ndx.cnt = count(str) + 1;
	quote.sq = 0;
	quote.dq = 0;
	ndx.check_space = 0;
	ndx.pipe = 0;
	tab = ft_calloc(1, (ndx.cnt + 1) * sizeof(char *));
	split_p0(str, &ndx, &quote, tab);
	return (tab);
}
