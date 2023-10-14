/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:09:57 by moelalj           #+#    #+#             */
/*   Updated: 2023/08/19 15:09:58 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == ':');
}

int	words_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] && !is_delimiter(s[i]))
		{
			i++;
			len++;
		}
		else
			i++;
	}
	return (len);
}

char	*get_word(char *str)
{
	int			i;
	char		*word;

	i = 0;
	while (str[i] && !is_delimiter(str[i]))
		i++;
	word = (char *)ft_calloc(1, sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && !is_delimiter(str[i]))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	int		i;
	char	**split;

	split = (char **)ft_calloc(1, sizeof(char *) * words_len(str) + 1);
	if (!split)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && is_delimiter(*str))
			str++;
		if (*str && !is_delimiter(*str))
		{
			split[i] = get_word(str);
			i++;
		}
		while (*str && !is_delimiter(*str))
			str++;
	}
	split[i] = NULL;
	return (split);
}
