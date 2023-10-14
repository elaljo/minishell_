/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_quote_split_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:38:25 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 18:38:58 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cnt_exp_p0(char *str, int i, t_quote *q)
{
	if (str[i] == '\'' && i != 0 && str[i - 1] != '\\' && \
		q->sq % 2 != 0 && q->dq % 2 != 0)
		q->sq++;
	else if (str[i] == '"' && i != 0 && str[i - 1] != '\\' \
		&& q->dq % 2 != 0 && q->sq % 2 != 0)
		q->dq++;
	else if (q->sq % 2 == 0 && i != 0 && str[i] == '\'' && \
		str[i - 1] != '\\')
		q->cnt++;
	else if (q->dq % 2 == 0 && i != 0 && str[i] == '"' && \
		str[i - 1] != '\\')
		q->cnt++;
	else if (q->sq % 2 != 0 && i != 0 && str[i] == '\'' && \
		str[i - 1] != '\\' && str[i - 1] != '\'' && \
		str[i - 1] != '"')
		q->cnt++;
	else if (q->dq % 2 != 0 && i != 0 && str[i] == '"' && \
		str[i - 1] != '\\' && str[i - 1] != '\'' && \
		str[i - 1] != '"')
		q->cnt++;
	else if (!str[i + 1])
		q->cnt++;
}

int	cnt_exp(char *str)
{
	int		i;
	t_quote	q;	

	q.cnt = 0;
	q.sq = 0;
	q.dq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && i == 0)
			q.sq++;
		else if (str[i] == '"' && i == 0)
			q.dq++;
		else if (str[i] == '\'' && i != 0 && str[i - 1] != '\\')
			q.sq++;
		else if (str[i] == '"' && i != 0 && str[i - 1] != '\\')
			q.dq++;
		cnt_exp_p0(str, i, &q);
		i++;
	}
	return (q.cnt);
}
