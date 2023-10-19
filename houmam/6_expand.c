/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p000.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:52:12 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/16 16:52:12 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_p0(t_exp *x)
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
			free(x->tmp);
		}
	}
	x->dollar_splitted = dollar_split(x->quote_splitted[x->j]);
	x->k = 0;
}

void	expander_p1(t_exp *x)
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
		free(x->tmp);
	}
	x->j++;
}

void	expander_p2(t_exp *x, t_data *data)
{
	if (x->dollar_splitted[x->k][2] == '\0')
	{
		if (g_exit_status)
		{
			x->tmp = ft_itoa(g_exit_status);
			g_exit_status = 0;
		}
		else
			x->tmp = ft_itoa(data->old_st);
		free(x->dollar_splitted[x->k]);
		x->dollar_splitted[x->k] = ft_strdup(x->tmp);
		free(x->tmp);
	}
	else if (x->dollar_splitted[x->k][2] != '\0')
	{
		x->tmp = ft_strdup(x->dollar_splitted[x->k]);
		free(x->dollar_splitted[x->k]);
		x->ito = ft_itoa(data->old_st);
		x->dollar_splitted[x->k] = ft_strjoin(x->ito, &x->tmp[2]);
		free(x->ito);
	}
}

void	expander_p3(t_exp *x, t_data *data)
{
	while (x->dollar_splitted[x->k] != NULL)
	{
		if (x->quoted != 1 && x->dollar_splitted[x->k][0] == '$' \
		&& x->dollar_splitted[x->k][1] == '?')
			expander_p2(x, data);
		else if (x->quoted != 1 && x->dollar_splitted[x->k][0] == '$' \
			&& is_var(x->dollar_splitted[x->k][1]) == 1)
		{
			x->tmp = ft_strdup(x->dollar_splitted[x->k]);
			free(x->dollar_splitted[x->k]);
			x->expand = expand_var(x->tmp, *data);
			x->dollar_splitted[x->k] = ft_strdup(x->expand);
			free(x->expand);
		}
		if (x->k == 0)
			x->joigned_0 = ft_strjoin("", x->dollar_splitted[x->k]);
		else if (x->k != 0)
		{
			x->tmp = ft_strdup(x->joigned_0);
			free(x->joigned_0);
			x->joigned_0 = ft_strjoin(x->tmp, x->dollar_splitted[x->k]);
			free(x->tmp);
		}
		x->k++;
	}
}

void	expander(t_cmd *cmd, int len, t_data *data)
{
	t_exp	x;

	x.argu = cmd->args;
	x.i = 0;
	x.empty = 0;
	while (x.i < len)
	{
		x.quote_splitted = quotes_split(x.argu[x.i]);
		x.j = 0;
		while (x.quote_splitted[x.j] != NULL)
		{
			expander_p0(&x);
			expander_p3(&x, data);
			expander_p1(&x);
		}
		ft_str_free(x.quote_splitted);
		free(x.argu[x.i]);
		x.argu[x.i] = ft_strdup(x.joigned_1);
		free(x.joigned_1);
		x.i++;
	}
}
