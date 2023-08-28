/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:24:26 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/27 20:24:27 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (0);
	return (1);
}

int	ft_isalnum(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] >= '0' && c[i] <= '9')
			|| (c[i] >= 'a' && c[i] <= 'z')
			|| (c[i] >= 'A' && c[i] <= 'Z')
			|| c[i] == '=' || c[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_str_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	len_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
