/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:36:33 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/23 17:36:35 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strback(char *line)
{
	int		i;
	char	*dest;

	i = 0;
	while (line[i] != '=' && line[i])
		i++;
	dest = (char *)ft_calloc(i + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (line[i] != '=' && line[i])
	{
		dest[i] = line[i];
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *s, char c)
{
	int		i;

	i = 0;
	while (1)
	{
		if (s[i] == c)
			return ((char *)&s[++i]);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (n > i)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, size * count);
	return (str);
}

int	ft_search(char *line, char space)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == space)
			return (1);
		i++;
	}
	return (0);
}
