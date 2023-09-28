/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:50:46 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/18 15:14:22 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_quoted(char *str)
{
	int len = ft_strlen(str) - 1;
	if (str[0] == '\'' && str[len] == '\'' && ft_strlen(str) != 1)
		return (1);
	if (str[0] == '"' && str[len] == '"')
		return (2);
	return (0);
}
char	*handle_quoted(char *str)
{
	int i;
	int j;
	int len;
	char *tmp;

	// printf("🔴 handle_quoted_fct --> %s 🔴\n", str);
	// while (check_quoted(str) != 0)
	// {
		tmp = ft_strdup(str);
		free(str);
		len = ft_strlen(tmp);
		str = malloc((len - 1) * sizeof(char));
		// printf("len - 1 --> %d\n", len - 1);
		i = 1;
		j = 0;
		while (i < len - 1)
		{
			str[j] = tmp[i];
			i++;
			j++;
		}
		str[j] = '\0';
		// printf("*🔴 handle_quoted_fct --> %s 🔴\n", str);
	// }
	// printf("🔴 handle_quoted_fct --> %s 🔴\n", str);
	return (str);
}
