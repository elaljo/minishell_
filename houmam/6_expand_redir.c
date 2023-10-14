/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:47:32 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 18:49:41 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_redir_p0(t_exp *x, t_data *data)
{
	if (x->quoted != 1 && x->dollar_splitted[x->k][0] == '$' \
		&& x->dollar_splitted[x->k][1] == '?')
	{
		if (x->dollar_splitted[x->k][2] == '\0')
		{
			x->tmp = ft_itoa(data->old_st);
			free(x->dollar_splitted[x->k]);
			x->dollar_splitted[x->k] = ft_strdup(x->tmp);
		}
		else if (x->dollar_splitted[x->k][2] != '\0')
		{
			x->tmp = ft_strdup(x->dollar_splitted[x->k]);
			free(x->dollar_splitted[x->k]);
			x->dollar_splitted[x->k] = \
			ft_strjoin(ft_itoa(data->old_st), &x->tmp[2]);
		}
	}
	else if (x->quoted != 1 && x->dollar_splitted[x->k][0] == '$' \
		&& is_var(x->dollar_splitted[x->k][1]) == 1)
	{
		x->tmp = ft_strdup(x->dollar_splitted[x->k]);
		free(x->dollar_splitted[x->k]);
		x->dollar_splitted[x->k] = ft_strdup(expand_var(x->tmp, *data));
	}
}

void	expand_redir_p1(t_exp *x)
{
	ft_str_free(x->dollar_splitted);
	if (x->empty == 1)
	{
		x->joigned_0 = ft_strdup("");
		x->empty = 0;
	}
	free(x->quote_splitted[x->j]);
	x->quote_splitted[x->j] = ft_strdup(x->joigned_0);
	free(x->joigned_0);
	if (x->j == 0)
		x->joigned_1 = ft_strjoin("", x->quote_splitted[x->j]);
	else
	{
		x->tmp = ft_strdup(x->joigned_1);
		free(x->joigned_1);
		x->joigned_1 = ft_strjoin(x->tmp, x->quote_splitted[x->j]);
	}
	x->j++;
}

void	expand_redir_p2(t_exp *x)
{
	x->quoted = check_quoted(x->quote_splitted[x->j]);
	if (x->quoted != 0)
	{
		if (ft_strlen(x->quote_splitted[x->j]) == 2)
		{
			free(x->quote_splitted[x->j]);
			x->quote_splitted[x->j] = NULL;
			x->empty = 1;
		}
		else
		{
			x->tmp = ft_strdup(x->quote_splitted[x->j]);
			free(x->quote_splitted[x->j]);
			x->quote_splitted[x->j] = handle_quoted(x->tmp);
		}
	}
	x->dollar_splitted = dollar_split(x->quote_splitted[x->j]);
}

void	expand_redir_p3(t_cmd *cmds, int i, int red, t_exp	*x)
{
	ft_str_free(x->quote_splitted);
	free(cmds[i].redii[red].eof);
	cmds[i].redii[red].eof = ft_strdup(x->joigned_1);
	free(x->joigned_1);
}

void	expand_redir(t_cmd *cmds, int i, int red, t_data *data)
{
	t_exp	x;

	x.empty = 0;
	x.quote_splitted = quotes_split(cmds[i].redii[red].eof);
	x.j = 0;
	while (x.quote_splitted[x.j] != NULL)
	{
		expand_redir_p2(&x);
		x.k = 0;
		while (x.dollar_splitted[x.k] != NULL)
		{
			expand_redir_p0(&x, data);
			if (x.k == 0)
				x.joigned_0 = ft_strjoin("", x.dollar_splitted[x.k]);
			else if (x.k != 0)
			{
				x.tmp = ft_strdup(x.joigned_0);
				free(x.joigned_0);
				x.joigned_0 = ft_strjoin(x.tmp, x.dollar_splitted[x.k]);
			}
			x.k++;
		}
		expand_redir_p1(&x);
	}
	expand_redir_p3(cmds, i, red, &x);
}
