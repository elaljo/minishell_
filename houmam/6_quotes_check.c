/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_quotes_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:46 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 17:21:37 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quoted(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (str[0] == '\'' && str[len] == '\'' && ft_strlen(str) != 1)
		return (1);
	if (str[0] == '"' && str[len] == '"')
		return (2);
	return (0);
}

char	*handle_quoted(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	tmp = ft_strdup(str);
	len = ft_strlen(tmp);
	str = ft_calloc(1, (len - 1) * sizeof(char));
	i = 1;
	j = 0;
	while (i < len - 1)
	{
		str[j] = tmp[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(tmp);
	return (str);
}
