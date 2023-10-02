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

#include "../../minishell.h"

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
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
	str = malloc(len_s1 + ft_strlen(s2) + 1 * sizeof(char));
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
char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}