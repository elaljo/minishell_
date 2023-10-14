/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:31:00 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 17:37:00 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_herdoc_p1(t_data *data, t_exp *x)
{
	if (x->dollar_splitted[x->k][0] == '$' && \
		is_var(x->dollar_splitted[x->k][1]) == 1)
	{
		x->tmp = ft_strdup(x->dollar_splitted[x->k]);
		free(x->dollar_splitted[x->k]);
		x->dollar_splitted[x->k] = ft_strdup(expand_var(x->tmp, *data));
	}
	if (x->k == 0)
		x->joigned_0 = ft_strjoin("", x->dollar_splitted[x->k]);
	else if (x->k != 0)
	{
		x->tmp = ft_strdup(x->joigned_0);
		free(x->joigned_0);
		x->joigned_0 = ft_strjoin(x->tmp, x->dollar_splitted[x->k]);
	}
	x->k++;
}

void	expand_herdoc(char **str, t_data *data)
{
	t_exp	x;

	x.dollar_splitted = dollar_split(*str);
	x.k = 0;
	while (x.dollar_splitted[x.k] != NULL)
		expand_herdoc_p1(data, &x);
	ft_str_free(x.dollar_splitted);
	free(*str);
	*str = ft_strdup(x.joigned_0);
	free(x.joigned_0);
}

void	expand_all(t_cmd *cmds, t_data *data)
{
	int	i;		

	i = 0;
	while (i < cmds->argu_nbr && cmds[i].args != NULL)
	{
		expander(&cmds[i], cmds[i].cmd_len, data);
		cmds[i].argu = rm_empty(cmds[i].args);
		i++;
	}
}
