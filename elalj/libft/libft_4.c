/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:51:21 by moelalj           #+#    #+#             */
/*   Updated: 2023/10/14 11:51:24 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_realloc(char **s, size_t size)
{
	char	**buff;
	int		i;

	i = 0;
	buff = ft_calloc(size + 1, sizeof(char *));
	if (buff)
	{
		while (s[i])
		{
			buff[i] = ft_strdup(s[i]);
			free(s[i]);
			i++;
		}
		free(s);
	}
	return (buff);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	len_s1;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	i = 0;
	str = ft_calloc(1, len_s1 + ft_strlen(s2) + 1 * sizeof(char));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[len_s1 + i] = s2[i];
		i++;
	}
	str[len_s1 + i] = '\0';
	return (str);
}

void	ft_str_free(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
