/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:49:01 by hait-sal          #+#    #+#             */
/*   Updated: 2023/10/14 11:59:11 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (1);
	}
	return (0);
}

int	nbr_l(int n)
{
	long	num;
	int		i;

	num = n;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		nl;
	char	*p;

	nb = n;
	nl = nbr_l(nb);
	p = ft_calloc (1, nl * sizeof(char) + 1);
	if (!p)
		return (NULL);
	if (n == 0)
		p[0] = 48;
	else if (nb < 0)
	{
		p[0] = 45;
		nb *= -1;
	}
	while (nb)
	{
		p[nl - 1] = nb % 10 + 48;
		nb /= 10;
		nl--;
	}
	p[nbr_l(n)] = 0;
	return (p);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
