/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_split_cmd_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:16:39 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 13:18:29 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_p2(char *str, t_quote *quote, int *i, int *prt)
{
	if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && str[*i] == '>' \
		&& str[(*i) + 1] && str[(*i) + 1] == '>')
	{
		(*prt)++;
		(*i)++;
	}
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && str[*i] == '<' \
		&& str[(*i) + 1] && str[(*i) + 1] == '<')
	{
		(*prt)++;
		(*i)++;
	}
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && !str[(*i) + 1] && \
		i != 0 && str[(*i) - 1] != '|' && str[(*i) - 1] != ' ' && \
		str[(*i) - 1] != '\t' && str[(*i) - 1] != '>' && str[(*i) - 1] != '<')
		(*prt)++;
}

void	count_p1(char *str, t_quote *quote, int *i, int *prt)
{
	if (*i == 0)
	{
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
	}
	if (str[*i] == 39)
		quote->sq++;
	if (str[*i] == 34)
		quote->dq++;
	if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && *i != 0 && \
	str[(*i) - 1] != '|' && str[(*i) - 1] != ' ' && str[*i] != '\t' && \
	str[(*i) - 1] != '>' && str[(*i) - 1] != '<' && (str[*i] == ' ' || \
	str[*i] == '\t'))
		(*prt)++;
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && str[*i] == '|')
		(*prt)++;
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && str[*i] == '>' \
		&& str[(*i) + 1] && str[(*i) + 1] != '>')
		(*prt)++;
	else if (quote->sq % 2 == 0 && quote->dq % 2 == 0 && str[*i] == '<' \
		&& str[(*i) + 1] && str[(*i) + 1] != '<')
		(*prt)++;
	else
		count_p2(str, quote, i, prt);
}

int	count(char *str)
{
	int		i;
	int		prt;
	t_quote	quote;

	quote.sq = 0;
	quote.dq = 0;
	i = 0;
	prt = 0;
	while (str[i])
	{
		count_p1(str, &quote, &i, &prt);
		i++;
	}
	return (prt);
}

void	removing_spaces(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		ft_trim(str, i);
}
