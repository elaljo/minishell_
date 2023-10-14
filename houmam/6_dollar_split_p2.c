/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_dollar_split_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:14:17 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 18:42:18 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cnt_dollars_p0(char *str, int *i, int *cnt)
{
	(*i)++;
	while (str[*i] && is_var(str[*i]) == 1)
		(*i)++;
	(*cnt)++;
}

int	cnt_dollars(char *str)
{
	int	i;
	int	cnt;

	if (!str)
		return (0);
	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && is_var(str[i + 1]) == 1)
			cnt_dollars_p0(str, &i, &cnt);
		else
		{
			while (str[i])
			{
				if (str[i] == '$' && str[i + 1] && is_var(str[i + 1]) == 1)
					break ;
				i++;
			}
			cnt++;
		}
	}
	return (cnt);
}

int	is_var(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| (c >= '0' && c <= '9') || c == '_' || c == '?');
}

char	*expand_var(char *str, t_data data)
{
	char	*tmp;

	tmp = ft_strdup(str);
	free(str);
	if (check_in_env(data, tmp + 1) == 1)
		str = ft_strdup(my_getenv(tmp + 1, &data));
	else
		str = ft_strdup("");
	free(tmp);
	return (str);
}

int	check_in_env(t_data data, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (data.c_env[i] != NULL)
	{
		if (ft_strncmp(data.c_env[i], var, len) == 0)
			return (1);
		i++;
	}
	return (0);
}
